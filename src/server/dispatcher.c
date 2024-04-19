#include "dispatcher.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "clientCnxManager.h"
#include "servCnxManager.h"
#include "syslog.h"
#include "grid.h"


// MESSAGE TYPES //
// 1 : hello
// 2 : startGame
// 3 : gridToClient
// 4 : gridToServer
// 5 : endGame

int playerCount = 0;

// grille partagée entre les deux joueurs
Grid *sharedGrid;

// Le client envoie un message de type 1 : hello au serveur
void hello(int sockfd){

    syslog(LOG_INFO, "dispatcher - hello - Start");

    printf("HELLO\n");

    message *message = malloc(sizeof(*message));
    
    // send message
    strcpy(message->type, "1");
    strcpy(message->data, "hello");
    strcpy(message->emmeteur, "Client");
    strcpy(message->destinataire, "Server");

    printf("Le serveur vous dit bonjour !\n");
    printf("####################\n");

    write(sockfd, message, sizeof(*message));

    // free message
    free(message);

    syslog(LOG_INFO, "dispatcher - hello - End");
}

// Le serveur envoie un message de type 3 : gridToClient au client
void startGame(int sockfd, int *playerCount){

    syslog(LOG_INFO, "dispatcher - startGame - Start");

    printf("START GAME\n");

    (*playerCount)++;

    message *message = malloc(sizeof(*message));

    // Si il y a deux joueurs, on envoie commencer la partie, sinon on envoie un message hello au client
    if (*playerCount == 2)
    {
        // allocation de la mémoire pour la grille partagée
        sharedGrid = malloc(sizeof(*sharedGrid));
        
        // create grid
        init_grid(sharedGrid, 5);

        // send the grid to the client (type 3 : gridToClient)
        strcpy(message->type, "3");
        for (int i = 0; i < 13; i++)
        {
            message->data[i] = sharedGrid->data[i];
        }
        strcpy(message->emmeteur, "Serveur");
        strcpy(message->destinataire, "Client");
        message->nbJetons = sharedGrid->nbJetons;

        printf("Envoi de la grille\n");

        // send message
        write(sockfd, message, sizeof(*message));
    }else{    
        // send hello message
        strcpy(message->type, "1");
        strcpy(message->data, "hello");
        strcpy(message->emmeteur, "Serveur");
        strcpy(message->destinataire, "Client");

        printf("Envoi du message start\n");

        // send message
        write(sockfd, message, sizeof(*message));
    }

    syslog(LOG_INFO, "dispatcher - startGame - End");
}

// Le serveur envoie un message de type 3 : gridToClient au client
void grid(message *message, int sockfd, int otherSockfd){

    syslog(LOG_INFO, "dispatcher - grid - Start");

    printf("GRID\n");

    // Grid *grid = malloc(sizeof(*grid));

    printf("Réception de la grille\n");

    // read the grid from the client
    for (int i = 0; i < 13; i++)
    {
        sharedGrid->data[i] = message->data[i];
    }
    sharedGrid->nbJetons = message->nbJetons;
    
    // grille copiée
    printf("Grille copiée\n");

    printf("grid : %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", sharedGrid->data[0], sharedGrid->data[1], sharedGrid->data[2], sharedGrid->data[3], sharedGrid->data[4], sharedGrid->data[5], sharedGrid->data[6], sharedGrid->data[7], sharedGrid->data[8], sharedGrid->data[9], sharedGrid->data[10], sharedGrid->data[11], sharedGrid->data[12]);

    // send the grid to the client (type 3 : gridToClient)
    strcpy(message->type, "3");
    for (int i = 0; i < 13; i++)
    {
        message->data[i] = sharedGrid->data[i];
    }
    strcpy(message->emmeteur, "Serveur");
    strcpy(message->destinataire, "Client");
    message->nbJetons = sharedGrid->nbJetons;    

    printf("Envoi du message grid\n");

    // send message
    write(otherSockfd, message, sizeof(*message));

    write(sockfd, message, sizeof(*message));

    // free message
    // free(message);

    syslog(LOG_INFO, "dispatcher - grid - End");
}

// Le client joue et envoie un message de type 4 : gridToServer au serveur ou un message de type 5 : endGame si la grille est gagnante
void play(message *message, int sockfd){

    syslog(LOG_INFO, "dispatcher - play - Start");

    printf("PLAY\n");

    sharedGrid = malloc(sizeof(*sharedGrid));

    // copie la grille pour pouvoir déplacer les jetons
    for (int i = 0; i < 13; i++)
    {
        sharedGrid->data[i] = message->data[i];
    }
    sharedGrid->nbJetons = message->nbJetons;

    // demande au joueur la position finale du jeton
    int finalPosition = 0;
    printf("Quelle est la position finale du jeton ?\n");
    scanf("%d", &finalPosition);

    // déplace le jeton
    moove_coin(sharedGrid, finalPosition);

    // verifie si la grille est gagnante
    int win = verify_grid(sharedGrid);

    // envoie un message de type 6 : endGame, si la grille est gagnante, sinon envoie un message de type 4 : gridToServer
    if (win == 1)
    {
        strcpy(message->type, "5");
        strcpy(message->data, "endGame");
        strcpy(message->emmeteur, "Client");
        strcpy(message->destinataire, "Serveur");

        // send message
        write(sockfd, message, sizeof(*message));
    }
    else
    {
        // send the grid to the server (type 4 : gridToServer)
        strcpy(message->type, "4");
        for (int i = 0; i < 13; i++)
        {
            message->data[i] = sharedGrid->data[i];
        }
        strcpy(message->emmeteur, "Client");
        strcpy(message->destinataire, "Serveur");
        message->nbJetons = sharedGrid->nbJetons;

        printf("Envoi du message grid\n");

        // send message
        write(sockfd, message, sizeof(*message));
    }
}

// Le serveur envoie un message de type 6 : endGame au client
void endGame(int sockfd){

    syslog(LOG_INFO, "dispatcher - endGame - Start");

    printf("END GAME\n");

    message *message = malloc(sizeof(*message));

    // send message
    strcpy(message->type, "5");
    strcpy(message->data, "endGame");
    strcpy(message->emmeteur, "Serveur");
    strcpy(message->destinataire, "Client");

    printf("Envoi du message endGame\n");

    // send message
    write(sockfd, message, sizeof(*message));

    syslog(LOG_INFO, "dispatcher - endGame - End");
}

void dispatchServ(char *msg, int sockfd, int otherSockfd){
    message message;

    memcpy(&message, msg, sizeof(message));

    printf("####################\n");
    printf("DISPATCHER\n");
    printf("message type : %s\n", message.type);
    // Verifie si le message est une grille
    if (sizeof(message.type) == "2" || message.type == "3", message.type == "4"){
        printf("message data : %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", message.data[0], message.data[1], message.data[2], message.data[3], message.data[4], message.data[5], message.data[6], message.data[7], message.data[8], message.data[9], message.data[10], message.data[11], message.data[12]);
    }else{
        printf("message data : %s\n", message.data);
    }
    printf("message emmeteur : %s\n", message.emmeteur);
    printf("message destinataire : %s\n", message.destinataire);
    printf("####################\n");

    switch (atoi(message.type))
    {
    case 1:
        // hello(sockfd);
        printf("Réception du message hello\n");
        break;
    case 2:
        // startGame message
        startGame(sockfd, &playerCount);
        break;
    case 3:
        // gridToClient message
        break;
    case 4:
        // gridToServer message
        grid(&message, sockfd, otherSockfd);
        break;
    case 5:
        // endGame message
        endGame(sockfd);
        break;
    default:
        break;
    }
}

void dispatchCli(char *msg, int sockfd){
    message message;

    memcpy(&message, msg, sizeof(message));

    printf("####################\n");
    printf("DISPATCHER\n");
    printf("message type : %s\n", message.type);
    // Verifie si le message est une grille
    if (sizeof(message.type) == "2" || message.type == "3", message.type == "4"){
        printf("message data : %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", message.data[0], message.data[1], message.data[2], message.data[3], message.data[4], message.data[5], message.data[6], message.data[7], message.data[8], message.data[9], message.data[10], message.data[11], message.data[12]);
    }else{
        printf("message data : %s\n", message.data);
    }    
    printf("message emmeteur : %s\n", message.emmeteur);
    printf("message destinataire : %s\n", message.destinataire);
    printf("message nbJetons : %d\n", message.nbJetons);
    printf("####################\n");

    switch (atoi(message.type))
    {
    case 1:
        // hello message si l'emetteur est différent de serveur (pour éviter les boucles infinies)
        // if (strcmp(message.emmeteur, "Serveur") != 0)
        hello(sockfd);
        break;
    case 2:
        printf("Réception du message start\n");
        break;
    case 3:
        // Reception d'un message grid -> action du joueur : message play
        printf("Réception de la grille\n");
        printf("Grille :\n %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | \n", message.data[0], message.data[1], message.data[2], message.data[3], message.data[4], message.data[5], message.data[6], message.data[7], message.data[8], message.data[9], message.data[10], message.data[11], message.data[12]);
        play(&message, sockfd);
        break;
    case 4:
        // gridToServer message
        break;
    case 5:
        printf("partie terminée\n");
        break;
    default:
        break;
    }
}