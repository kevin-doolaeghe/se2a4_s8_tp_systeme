#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define NB          10
#define CLE_MSG     (key_t) 1000
#define TAILLE_MSG  20

struct sigaction action;

typedef struct {
    long type;
    char texte[TAILLE_MSG];
} message_t;

static int msgid;

void handler(int signal) {
    printf("Signal SIGINT reçu, destruction de la file\n");
    msgctl(msgid, IPC_RMID, 0);
    exit(SIGINT);
}

int main() {
    message_t message;

    action.sa_handler = handler;
    sigaction(SIGINT, &action, NULL);

    if ((msgid = msgget(CLE_MSG, IPC_CREAT|IPC_EXCL|0666)) == 1) {
        perror ("msgget");
        exit(1);
    }

    while (1) {
        msgrcv(msgid, &message, TAILLE_MSG, 1, 0);
        
        printf("message reçu par pong = %s\n", message.texte);
        sleep(1);

        strcpy(message.texte, "message de type 2\n");
        message.type = 2;
        msgsnd(msgid, &message, TAILLE_MSG, 0);
    }

    return 0;
}
