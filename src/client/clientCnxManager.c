#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "client/clientCnxManager.h"
#include "dispatcher.h"

void *threadProcessCli(void * ptr) {
    char buffer_in[BUFFERSIZE];
    int sockfd = *((int *) ptr);
    int len;
    while ((len = read(sockfd, buffer_in, BUFFERSIZE)) != 0) {
        // if (strncmp(buffer_in, "exit", 4) == 0) {
        //     break;
        // }

        // printf("receive %d chars\n", len);
        // printf("%.*s\n", len, buffer_in);

        dispatchCli(buffer_in, sockfd);

        //clear input buffer
        memset(buffer_in, '\0', BUFFERSIZE);
    }
    close(sockfd);
    printf("client pthread ended, len=%d\n", len);
}

int open_connection() {
    int sockfd;

    struct sockaddr_in serverAddr;
    int port = 7799;

    // Create the socket. 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Configure settings of the server address
    // Address family is Internet 
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function 
    serverAddr.sin_port = htons(port);
    //Set IP address to localhost
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    //Connect the socket to the server using the address
    if (connect(sockfd, (struct sockaddr *) &serverAddr, sizeof (serverAddr)) != 0) {
        printf("Fail to connect to server");
        exit(-1);
    };

    return sockfd;
}
