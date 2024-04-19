#include "grid.h"
/* 
 * File:   message.h
 * Author: Gaston Bouvier
 *
 */

#ifndef MESSAGE_H

#define MESSAGE_H

typedef struct {
    char type[20];
    char data[20];
    int nbJetons;
    char emmeteur[20];
    char destinataire[20];
} message;


#endif /* MESSAGE_H */