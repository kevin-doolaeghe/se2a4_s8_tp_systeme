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

    int nb1, nb2, op;
    
    printf("Addition = 0 | Multiplication = 1\n");
    printf("Entrer une opération : ");
    scanf("%d", &op);
    
    printf("Entrer un premier nombre : ");
    scanf("%d", &nb1);
    
    printf("Entrer un second nombre : ");
    scanf("%d", &nb2);

    int i, j;

    for (i = 0; i < TAILLE_MSG; i++)
        message.texte[i] = 0;

    for (i = 3; i >= 0; i--) {
        message.texte[3 - i] = (nb1 >> (8 * i)) & 0xFF;
        message.texte[7 - i] = (nb2 >> (8 * i)) & 0xFF;
    }

    printf("Contenu du message bits par bits :\n");
    for (i = 0; i < TAILLE_MSG; i++) {
        for (j = 0; j < 8; j++) {
            if (((message.texte[i] >> (7 - j)) & 0x01) == 0)
                printf("0");
            else
                printf("1");
        }
        printf("\n");
    }

    switch (op) {
    case 0:
        message.type = 10;
        break;
    case 1:
        message.type = 20;
        break;
    }

    msgsnd(msgid, &message, TAILLE_MSG, 0);

    msgrcv(msgid, &message, TAILLE_MSG, 30, 0);

    printf("Réponse : %s\n", message.texte);

    return 0;
}
