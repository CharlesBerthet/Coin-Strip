
/* 
 * File:   grid.h
 * Author: Gaston Bouvier
 *
 */

#ifndef GRID_H

#define GRID_H
#define GRID_ARRAY_MAX_SIZE 13

typedef struct {
    int data[GRID_ARRAY_MAX_SIZE];
    int nbJetons;
} Grid;

void init_grid(Grid *g,int nbJetons);
int moove_coin(Grid *g, int finalPosition); // Renvoie true si l'action est possible
int verify_grid(Grid *g); // Renvoie true si le joueur a gagné

#endif /* GRID_H */