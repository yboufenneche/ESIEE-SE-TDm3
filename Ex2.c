#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestionFichiers.h"
#define R 0
#define W 1
//
void ilEstTropTard()
{
    printf("Trop tard: coffre-fort ferme\n");
    exit(0);
}
//
int main()
{
    char *c;
    int pid;
    pid = fork();
    if (pid == 0)
    {
        printf("Entrez le bon code secret en moins de 10 secondes\n");
        // On installe le gestionnaire de signal ilEstTropTard
        if (signal(SIGUSR1, &ilEstTropTard) == SIG_ERR)
        {
            printf("Ne peut pas gerer le signal \n");
            return 0;
        }
        if ((c = litLigne(R)) == NULL)
        {
            printf("Erreur de lecture d'une ligne au clavier\n");
        }
        if (strlen(c) != 5)
        {
            printf("Code faux : coffre fort ferme\n");
            exit(0);
        }
        if ((c[0] != '1') ||
            (c[1] != '2') ||
            (c[2] != '3') ||
            (c[3] != '4'))
        {
            printf("Code faux : coffre fort ferme\n");
            exit(0);
        }
        printf("Bravo : coffre-fort ouvert\n");
        exit(0);
    }
    else
    {
        sleep(10);
        kill(pid, SIGUSR1);
        wait(NULL);
        printf("Programme termine\n");
    }
    return 1;
}