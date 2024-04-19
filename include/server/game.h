#include "../common/grid.h"
#include "player.h"
/* 
 * File:   game.h
 * Author: Gaston Bouvier
 *
 */

#ifndef GAME_H

#define GAME_H

typedef struct {
    int nbTurn;
    int playerTurn;
    Grid grid;
    Player player1;
    Player player2;
} Game;

void initGame(Player player1, Player player2);
int moove_coin(Grid g, int finalPosition); // Renvoie true si l'action est possible
int verify_grid(Grid g); // Renvoie true si le joueur a gagné
int isPlayerTurn(Player p);

#endif /* GAME_H */