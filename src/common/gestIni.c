/* 
 * File:   gestINI.c
 * Author: Gaston Bouvier
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <syslog.h>

int initIniFile(char *Pseudo) 
{
    FILE *fichier;
    fichier = fopen("conf.ini", "w, ccs=UTF-8");
    syslog(LOG_INFO, "gestIni - initIniFile - Pseudo : %s", Pseudo);


    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier \n");
        syslog(LOG_ERR, "gestIni - initIniFile - Impossible d'ouvrir le fichier ");
        return 0;
    }


    fprintf(fichier, "; \n");
    fprintf(fichier, "[Player] \n");
    fprintf(fichier, "NAME =%s \n", Pseudo);
    fprintf(fichier, "[Serveur] \n");
    // fprintf(fichier, "servIP =%s \n",);

    fprintf(fichier, "[App Info] \n");
    fprintf(fichier, "Version = 0.1 \n");

    fclose(fichier);
    syslog(LOG_INFO, "gestIni - initIniFile - End ");
}

