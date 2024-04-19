// void *threadProcessServ(void *ptr) {
//     char buffer_in[BUFFERSIZE];
//     char buffer_out[BUFFERSIZE];

//     int len;
//     connection_t *connection;

//     if (!ptr) pthread_exit(0);
//     connection = (connection_t *) ptr;
//     printf("Nouvelle connexion\n");

//     add(connection);

//     int otherSockfd;

//     // Attendez que les deux clients soient connectés
//     while (connections[0] == NULL || connections[1] == NULL) {
//         sleep(1); // Attendre 1 seconde avant de vérifier à nouveau
//     }

//     while ((len = read(connection->sockfd, buffer_in, BUFFERSIZE)) > 0) {
        
//         // On récupère le socket de l'autre client
//         if (connection->index == 0) {
//             otherSockfd = connections[1]->sockfd;
//         } else {
//             otherSockfd = connections[0]->sockfd;
//         }
 

//         // Appel du dispatcher
//         dispatchServ(buffer_in, connection->sockfd, otherSockfd);

//         if (strncmp(buffer_in, "bye", 3) == 0) {
//             break;
//         }

//         // Nettoyage du buffer
//         memset(buffer_in, '\0', BUFFERSIZE);
//     }
//     printf("Connection to client %i ended \n", connection->index);
//     close(connection->sockfd);
//     del(connection);
//     free(connection);
//     pthread_exit(0);

// }