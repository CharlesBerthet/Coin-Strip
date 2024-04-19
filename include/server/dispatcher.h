#include "message.h"

#ifndef DISPATCHER_H

#define DISPATCHER_H

void hello(int sockfd);
void startGame(int sockfd, int *playerCount);
void gridToClient(int sockfd, Grid *sharedGrid);
void gridToServer(int sockfd, Grid *sharedGrid);
void endGame(int sockfd);
void dispatchServ(char *msg, int sockfd, int otherSockfd);
void dispatchCli(char *msg, int sockfd);

#endif /* DISPATCHER_H */