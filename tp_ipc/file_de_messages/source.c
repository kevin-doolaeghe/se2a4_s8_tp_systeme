#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NB  10
#define CLE_MSG  (key_t)1000
#define TAILLE_MSG 20

/* définition de la structure des messages */
typedef struct {
    long type;
    char texte[TAILLE_MSG];
} Msg_requete;

int main() {
    int msgid, n ;
    Msg_requete message;
    /* création de la FDM */
    if ((msgid = msgget(CLE_MSG, IPC_CREAT|IPC_EXCL|0666)) == 1) {
        perror ("msgget");
        exit(1);
    }

    /* création du processus fils */
    if ((n=fork()) == 1) {
        perror ("fork");
        exit(2);
    }
    if (n==0){
        /* on est dans le fils */
        /* reception du message du père : message de type 1 */
        msgrcv(msgid, &message, TAILLE_MSG, 1, 0);
        
        /* affichage contenu message */
        printf("message reçu par le fils = %s\n", message.texte);
        /* preparation de l'ack : message de type 2 */
        message.type = 2;
        strcpy(message.texte, "msg reçu\n");

        /* envoi de l'ack au père */
        msgsnd(msgid, &message, TAILLE_MSG, 0);
    } else {
        /* on est dans le père */
        /* preparation du message */
        message.type = 1 ;
        strcpy(message.texte, "hello\n");

        /* envoi du message au fils */
        msgsnd(msgid, &message, TAILLE_MSG, 0);
        /* attente de reception de l'ack : message de type 2 */
        msgrcv(msgid, &message, TAILLE_MSG, 2, 0);
        /* affichage ack reçu */
        printf("ack reçu par père : %s\n", message.texte);

        /* attente de la mort du fils */
        wait(NULL);
        /* destruction de la fdm */
        msgctl(msgid, IPC_RMID, 0);
    }
}
