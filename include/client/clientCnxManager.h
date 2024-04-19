/* 
 * File:   clientCxnManager.h
 * Author: Alexandre
 *
 */

#ifndef CLIENTCXNMANAGER_H
#define CLIENTCXNMANAGER_H

#define BUFFERSIZE 2048

void *threadProcessCli(void * ptr);
int open_connection();

#endif /* CLIENTCXNMANAGER_H */
