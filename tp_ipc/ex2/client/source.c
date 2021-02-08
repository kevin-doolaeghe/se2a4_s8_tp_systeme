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
    printf("Entrer une opération :");
    scanf("%d", &op);
    
    printf("Entrer un premier nombre :");
    scanf("%d", &nb1);
    
    printf("Entrer un second nombre :");
    scanf("%d", &nb2);

    char str[TAILLE_MSG];
   
    strcat(str, (char)(nb1 >> 24) & 0xFF);
    strcat(str, (char)(nb1 >> 16) & 0xFF);
    strcat(str, (char)(nb1 >> 8) & 0xFF);
    strcat(str, (char)nb1 & 0xFF);
    strcat(str, ",");
    strcat(str, (char)(nb2 >> 24) & 0xFF);
    strcat(str, (char)(nb2 >> 16) & 0xFF);
    strcat(str, (char)(nb2 >> 8) & 0xFF);
    strcat(str, (char)nb2 & 0xFF);
    
    strcpy(message.texte, str);
    
    switch (op) {
    case 0:
        message.type = 10;
    case 1:
        message.type = 20;
    }

    msgsnd(msgid, &message, TAILLE_MSG, 0);

    msgrcv(msgid, &message, TAILLE_MSG, 2, 0);

    printf("Réponse : %s\n", message.texte);

    return 0;
}
