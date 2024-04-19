#include "grid.h"
#include <client/clientCnxManager.h>
#include <server/servCnxManager.h>
/* 
 * File:   sendGrid.h
 * Author: Gaston Bouvier
 *
 */

#ifndef SENDGRID_H

#define SENDGRID_H

typedef struct {
    int messageId;
    int data[GRID_ARRAY_MAX_SIZE];
    int nbJetons;
} sendGrid;

void sendTheGrid(Grid *g, connection_t *connection);
void *threadSendGrid (void *ptr);
void *threadReadGrid (void *ptr);

#endif /* SENDGRID_H */