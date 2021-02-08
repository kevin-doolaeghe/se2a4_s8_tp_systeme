#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define NB          10
#define CLE_MSG     (key_t) 1000
#define TAILLE_MSG  20

typedef struct {
    long type;
    char texte[TAILLE_MSG];
} message_t;

int msgid;

int main() {
    message_t message;
    
    if ((msgid = msgget(CLE_MSG, IPC_CREAT|0666)) == 1) {
        perror ("msgget");
        exit(1);
    }

    time_t start = time(NULL);
    
    strcpy(message.texte, "message de type 1\n");
    message.type = 1;
    msgsnd(msgid, &message, TAILLE_MSG, 0);
    
    msgrcv(msgid, &message, TAILLE_MSG, 2, 0);

    time_t end = time(NULL);

    printf("message reçu par ping = %s\n", message.texte);

    printf("temps d'aller-retour = %lis\n", end - start);

    return 0;
}
