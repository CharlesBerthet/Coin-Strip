/* 
 * File:   selector.c
 * Author: aurelio
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "server/servCnxManager.h"
#include "client/clientCnxManager.h"

#include "common/grid.h"
#include "common/gridManager.h"

#include "dispatcher.h"
#include "message.h"
/*
 *
 */

int mainServ(int argc, char** argv) {

    int sockfd = -1;
    int index = 1;
    connection_t *connection;
    pthread_t thread;

    /* init array*/
    init_sockets_array();
    /* create socket */
    sockfd = create_server_socket();

    /* listen on port , stack size 50 for incoming connections*/
    if (listen(sockfd, 50) < 0) {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }

    printf("ready and listening\n");

    //Wait for connection
    while (true) {
        /* accept incoming connections */
        connection = (connection_t *) malloc(sizeof (connection_t));
        connection->sockfd = accept(sockfd, &connection->address, &connection->addr_len);
        connection->index = index++;
        if (connection->sockfd <= 0) {
            free(connection);
        } else {
            /* start a new thread (connexion) but do not wait for it */
            pthread_create(&thread, 0, threadProcessServ, (void *) connection);

            pthread_detach(thread);
        }

    }
    return (EXIT_SUCCESS);
}

int mainCli() {

    int sockfd;
    int status = 0;
    char msg[100];
    pthread_t thread;

    message *message = malloc(sizeof(*message));

    sockfd = open_connection();

    // send start message
    strcpy(message->type, "2");
    strcpy(message->data, "start");
    strcpy(message->emmeteur, "Client");
    strcpy(message->destinataire, "Serveur");
    printf("Envoi du message start\n");
    write(sockfd, message, sizeof(*message));

    //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcessCli, &sockfd);

    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(thread);
    
    do {
        
    } while (status != -1);

    return (EXIT_SUCCESS);
}