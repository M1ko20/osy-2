#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char*argv[])
{
    int N = atoi(argv[2]);

    char jmena[1000][255]; 
    int pocet_jmen = 0;

      FILE *soubor = fopen(argv[1], "r");
    if (!soubor) {
        fprintf(stderr, "Chybka, tohle fungovat nebude");
        return 1;
    }

    while (fgets(jmena[pocet_jmen], 255, soubor)) {
        // Odstranit newline na konci
        jmena[pocet_jmen][strcspn(jmena[pocet_jmen], "\n")] = '\0';
        pocet_jmen++;
    }


    fclose(soubor);
    int roura1[2];
    if (pipe(roura1) == -1)
    {
        printf("chyba");
        return -1;
    }

    int roura2[2];
    if (pipe(roura2) == -1)
    {
        printf("chyba");
        return -1;
    }

    int roura3[2];
    if (pipe(roura3) == -1)
    {
        printf("chyba");
        return -1;
    }


    int roura4[2];
    if (pipe(roura4) == -1)
    {
        printf("chyba");
        return -1;
    }

    // 1. vybira jmena
    if (fork() == 0)
    {
        close(roura1[1]);
        close(roura2[0]);
        close(roura3[0]);
        close(roura3[1]);
        close(roura4[0]);
        close(roura4[1]);
        
        FILE *stream = fdopen(roura1[0], "r");
        if (!stream) {
            perror("fdopen");
            exit(1);
        }
        
        char buffer[256];
        while (fgets(buffer, 256, stream))
        {
            int cislo, pid;
            if (sscanf(buffer, "%d (%d)", &cislo, &pid) == 2) {
                dprintf(roura2[1], "%s (%d) (%d)\n", jmena[cislo], pid, getpid());
            }
        }
        
        close(roura1[0]);
        close(roura2[1]);
        exit(0);
    }

    // 2 - cisluje
    if (fork() == 0)
    {   
        close(roura1[0]);
        close(roura1[1]);
        close(roura2[1]);
        close(roura3[0]);
        close(roura4[0]);
        close(roura4[1]);
        
        FILE* stream2 = fdopen(roura2[0], "r");
        if (stream2 == NULL)
        {
            exit(1);
        }
        
        char buffer[256];
        int poradi = 1;
        
        while (fgets(buffer, sizeof(buffer), stream2))
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            dprintf(roura3[1], "%d. %s (%d)\n", poradi, buffer, getpid());
            poradi++;
        }
        
        close(roura2[0]);
        close(roura3[1]);
        exit(0);
    }

    // 3. kratke pise, 4. dal
    if (fork() == 0)
    {
        close(roura1[0]);
        close(roura1[1]);
        close(roura2[1]);
        close(roura2[0]);
        close(roura3[1]);
        close(roura4[0]);
        
        FILE* stream3 = fdopen(roura3[0], "r");
        if (stream3 == NULL)
        {
            exit(1);
        }
        
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), stream3))
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            
            // "1. Adam (pid1) (pid2) (pid3)"
            char* dot = strchr(buffer, '.');
            if (!dot) continue;
            
            char* space = dot + 2; 
            char* bracket = strchr(space, ' ');
            if (!bracket) continue;
            
            int jmeno_delka = bracket - space;
            char jmeno[256];
            strncpy(jmeno, space, jmeno_delka);
            jmeno[jmeno_delka] = '\0';
            
            if (strlen(jmeno) < N)
            {
                printf("%s (%d)\n", buffer, getpid());
                fflush(stdout);
            }
            else
            {
                dprintf(roura4[1], "%s (%d)\n", buffer, getpid());
            }
        }
        
        close(roura3[0]);
        close(roura4[1]);
        exit(0);
    }

    //4 - dlouhe
    if (fork() == 0)
    {
        close(roura1[0]);
        close(roura1[1]);
        close(roura2[0]);
        close(roura2[1]);
        close(roura3[0]);
        close(roura3[1]);
        close(roura4[1]);
        
        FILE* stream4 = fdopen(roura4[0], "r");
        if (stream4 == NULL)
        {
            exit(1);
        }
        
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), stream4))
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            printf("%s", buffer);
            printf(" (%d) \n", getpid());
            fflush(stdout);
        }
        
        close(roura4[0]);
        exit(0);
    }

    // Rodičovský proces - posílá náhodná čísla prvnímu potomkovi
    close(roura1[0]);
    close(roura2[0]);
    close(roura2[1]);
    close(roura3[0]);
    close(roura3[1]);
    close(roura4[0]);
    close(roura4[1]);
    
    srand(time(NULL));

    int kolik = (getpid() % 20) + 5;  // Omezit na 5-24 řádků

    for (int i = 0; i < kolik; i++) {
        int nahodne_cislo = rand() % pocet_jmen;
        dprintf(roura1[1], "%d (%d)\n", nahodne_cislo, getpid());
        usleep((rand() % 51 + 50) * 1000);
    }

    close(roura1[1]); 
    
    // Čekat na všechny 4 potomky
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}