#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestionFichiers.h"
/* Réponse à la question 1−B−1 est : un tube, un tube nommé. On ne */
/* peut pas utiliser un fichier car pas de synchronisation. */
#define R 0
#define W 1
int main()
{
    int fd, fdTrans[2];
    char *c;
    int i = 0;
    if (pipe(fdTrans) == -1)
    {
        fprintf(stderr, "Ne peut ouvrir de tubes \n");
        return 0;
    }
    if (fork() != 0)
    { // processus pere
        close(fdTrans[R]);
        if ((fd = open("./Source.txt", O_RDONLY)) == -1)
        {
            printf("Ne peut ouvrir le fichier Source\n");
            return 0;
        }
        while ((c = litLigne(fd)) != NULL)
        {
            ecritLigne(fdTrans[W], c);
            free(c);
            i++;
        }
        printf("Pere termine %d lignes lues\n", i);
        close(fdTrans[W]);
        wait(NULL);
    }
    else
    {
        close(fdTrans[W]);
        if ((fd = open("./Destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0700)) == 1)
        {
            printf("Ne peut ouvrir le fichier Destination\n");
            return 0;
        }
        while (c = litLigne(fdTrans[R]))
        {
            ecritLigne(fd, c);
            free(c);
            i++;
        }
        printf("Fils termine, %d lignes lues\n", i);
        close(fdTrans[R]);
    }
    return 0;
}