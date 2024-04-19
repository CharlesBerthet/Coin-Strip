#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <client/clientCnxManager.h>
#include <server/servCnxManager.h>
#include <common/grid.h>
#include <common/gridManager.h>

void sendTheGrid(Grid *g, connection_t *connection){
    syslog(LOG_INFO, "Grid - sendGrid - Start");

    // instancie un objet sendGrid
    sendGrid sg;

    sg.messageId = 1;
    sg.nbJetons = g->nbJetons;
    memcpy(sg.data, g->data, sizeof(g->data));

    // Envoie de la grille aux clients
    write(connection->sockfd, &sg, sizeof(sendGrid));

    syslog(LOG_INFO, "sendGrid - sendTheGrid - End");
}

void *threadSendGrid (void *ptr) {
    syslog(LOG_INFO, "sendGrid - threadSendGrid - Start");

    connection_t *connection;
    connection = (connection_t *) ptr;

    Grid g;
    init_grid(&g, 5);
    printf("grid initialized\n");
    sendTheGrid(&g, connection);

    syslog(LOG_INFO, "sendGrid - threadSendGrid - End");
}

// Read the grid from the client
void *threadReadGrid (void *ptr) {
    syslog(LOG_INFO, "sendGrid - threadReadGrid - Start");

    int sockfd;
    sockfd = *(int *) ptr;

    sendGrid sg;
    read(sockfd, &sg, sizeof(sendGrid));
    printf("messageId : %d\n", sg.messageId);
    printf("nbJetons : %d\n", sg.nbJetons);
    printf("data : %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", sg.data[0], sg.data[1], sg.data[2], sg.data[3], sg.data[4], sg.data[5], sg.data[6], sg.data[7], sg.data[8], sg.data[9], sg.data[10], sg.data[11], sg.data[12]);

    syslog(LOG_INFO, "sendGrid - threadReadGrid - End");
}