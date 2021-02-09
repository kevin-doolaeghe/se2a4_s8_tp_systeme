#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>

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

void *add(void *arg) {
    message_t msg = *(message_t *) arg;
    
    int a = 0, b = 0;
    int i;
    for (i = 0; i < 8; i++) {
        if (i < 4) {
            a |= msg.texte[i] << (8 * (3 - i));
        } else {
            b |= msg.texte[i] << (8 * (3 - (i - 4)));
        }
    }

    printf("a = %d\nb = %d\na + b = ", a, b);

    return a + b;
}

void *mult(void *arg) {
    message_t msg = *(message_t *) arg;
    
    int a = 0, b = 0, i;
    
    for (i = 3; i >= 0; i--) {
        a += msg.texte[3 - i] << (8 * i);
        b += msg.texte[7 - i] << (8 * i);
    }
    printf("a = %d\nb = %d\na x b = ", a, b);

    return a * b;
}

int main() {
    message_t message;

    if ((msgid = msgget(CLE_MSG, IPC_CREAT|IPC_EXCL|0666)) == 1) {
        perror ("msgget");
        exit(1);
    }

    action.sa_handler = handler;
    sigaction(SIGINT, &action, NULL);

    int res;

    while (1) {
        msgrcv(msgid, &message, TAILLE_MSG, -20, 0);
        
        printf("message reçu de type %li\n", message.type);
        printf("contenu du message :\n");
        int i, j;
        for (i = 0; i < TAILLE_MSG; i++) {
            for (j = 0; j < 8; j++) {
                if (((message.texte[i] >> (7 - j)) & 0x01) == 0)
                    printf("0");
                else
                    printf("1");
            }
            printf("\n");
        }
        printf("\n");
        
        pthread_t tid;

        switch (message.type) {
        case 10:
            pthread_create(&tid, NULL, add, (void *) &message);
            break;
        case 20:
            pthread_create(&tid, NULL, mult, (void *) &message);
            break;
        }
        pthread_join(tid, (void *) &res);

        printf("%d\n********************************************\n", res);

        strcpy(message.texte, "ACK\n");
        message.type = 30;
        msgsnd(msgid, &message, TAILLE_MSG, 0);
    }

    return 0;
}
