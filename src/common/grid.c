/* 
 * File:   grid.c
 * Author: Gaston Bouvier
 *
 */

#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <client/clientCnxManager.h>
#include <server/servCnxManager.h>



/**
 * Initializes the grid with the specified number of tokens.
 *
 * @param g         Pointer to the Grid structure.
 * @param nbJetons  The number of tokens to be initialized.
 */
void init_grid(Grid *g,int nbJetons){
    syslog(LOG_INFO, "Grid - init_grid - nbJetons : %d", nbJetons);
    int i;
    g->nbJetons=nbJetons;
    for(i=0;i<GRID_ARRAY_MAX_SIZE;i++){
        g->data[i]=0;
    }
    int n = 0;
    while (n<5)
    {
        int randomNumber = rand() % 13;
        if(g->data[randomNumber]==0){
            g->data[randomNumber]=1;
            n++;
        }
    }
    printf("grid : %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n", g->data[0],g->data[1],g->data[2],g->data[3],g->data[4],g->data[5],g->data[6],g->data[7],g->data[8],g->data[9],g->data[10],g->data[11],g->data[12]);
    syslog(LOG_INFO, "Grid - init_grid - grid : %d,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", g->data[0],g->data[1],g->data[2],g->data[3],g->data[4],g->data[5],g->data[6],g->data[7],g->data[8],g->data[9],g->data[10],g->data[11],g->data[12]);
}; 


/**
 * @brief Verifies the grid by counting the number of coins present.
 * 
 * This function counts the number of coins present in the grid and checks if it is equal to 5.
 * 
 * @param g Pointer to the Grid structure.
 * @return Returns 1 if the number of coins is equal to 5, otherwise returns 0.
 */
int verify_grid(Grid *g){
    syslog(LOG_INFO, "Grid - verify_grid - Start - grid : %d,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", g->data[0],g->data[1],g->data[2],g->data[3],g->data[4],g->data[5],g->data[6],g->data[7],g->data[8],g->data[9],g->data[10],g->data[11],g->data[12]);
    int compteur = 0;
    int i = 0;

    for(i=0;i<g->nbJetons;i++){
        if(g->data[i]==1){
            compteur++;
        }
    }
    if(compteur==5){
        syslog(LOG_INFO, "Grid - verify_grid - End - 1");
        return 1;
    }
    syslog(LOG_INFO, "Grid - verify_grid - End - 0");
    return 0;
};

/**
 * Moves a coin in the grid to the specified final position.
 * 
 * @param g The grid object.
 * @param finalPosition The final position to move the coin to.
 * @return 0 if the coin was successfully moved, 1 otherwise.
 */
int moove_coin(Grid *g, int finalPosition){
    syslog(LOG_INFO, "Grid - moove_coin - Start - finalPosition : %d grid : %d,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", finalPosition, g->data[0],g->data[1],g->data[2],g->data[3],g->data[4],g->data[5],g->data[6],g->data[7],g->data[8],g->data[9],g->data[10],g->data[11],g->data[12]);
    int index = finalPosition-1;
    finalPosition = finalPosition - 1;

    int fin = 0;

    // Verif si il a un jeton sur la case
    if (g->data[finalPosition] == 0)
    {
        // Verif le prochain jeton sur la droite
        while (fin == 0)
        {
            if (g->data[index] == 1)
            {
                printf("\nEchange du coin de la position %d à la position %d\n",index,finalPosition);
                g->data[finalPosition] = 1;
                g->data[index] = 0;
                fin = 1;
                syslog(LOG_INFO, "Grid - moove_coin - End - grid : %d,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", g->data[0],g->data[1],g->data[2],g->data[3],g->data[4],g->data[5],g->data[6],g->data[7],g->data[8],g->data[9],g->data[10],g->data[11],g->data[12]);
                return 0;
            }
            else
            {
                index++;

                if(index>12){
                    syslog(LOG_INFO, "Grid - moove_coin - End - error type : 2");
                    chooseAgain(g, 2);
                    return 0;
                }
            }         
        }
        syslog(LOG_INFO, "Grid - moove_coin - End - 1A");  
        return 1;  
    }
    else{
        syslog(LOG_INFO, "Grid - moove_coin - End - choose case with coin");  
        chooseAgain(g, 1);
    }
    syslog(LOG_INFO, "Grid - moove_coin - End - 1B");  
    return 1;
};

/**
 * @brief Chooses a case to move a coin to.
 * 
 * This function asks the user to choose a case to move a coin to, it's a second 
 * 
 * @param g Pointer to the Grid structure.
 * @param errorType The type of error that occurred.
 */
void chooseAgain(Grid *g, int errorType){
    syslog(LOG_INFO, "Grid - chooseAgain - Start -  grid : %d,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", g->data[0],g->data[1],g->data[2],g->data[3],g->data[4],g->data[5],g->data[6],g->data[7],g->data[8],g->data[9],g->data[10],g->data[11],g->data[12]);
    int index;
    
    // Sélection des différentes cas d'erreurs
    if(errorType==1){
        printf("\nAction impossible, il y a déjà un jeton sur cette case, \n");
        printf("Veuillez choisir une case vide : \n");
    }
    else if(errorType==2){
        printf("\nAction impossible, il n'y a pas de jeton à droite, \n");
        printf("Veuillez entrer une case fonctionnelle :\n");
    }
    else if(errorType==3){
        printf("\nLA valeur entrée n'existe pas\n");
        printf("Veuillez entrer une case fonctionnelle :\n");
    }

    // On entre la valeur à la main
    scanf("%d", &index);
    if(index>13 || index<1){
        syslog(LOG_INFO, "Grid - chooseAgain - End - error type : 3");
        // La valeur entrée n'est pas bonne
        chooseAgain(g, 3);
    }

    // On lance la fonction moove_coin avec la valeur entrée
    moove_coin(g, index);
};