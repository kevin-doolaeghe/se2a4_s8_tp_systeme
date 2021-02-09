#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "serveur.h"


int main(void)
{
	int msgid;
	int operation,a,b;

	if((msgid = msgget(CLE_MSG,IPC_EXCL|0600))==-1)
	{
		perror("recuperation file de message");
		exit(1);
	}

	printf("Veuillez entrer l'opération à effectuer\n");
	printf("1: addition \t 2: multiplication\n");
	scanf("%d",&operation);
	printf("Veuiller entrer les deux valeurs\n");
	scanf("%d %d",&a,&b);

	mymsg_t msg;
	msg.type = operation*10;
	msg.a = a;
	msg.b = b;

	if(msgsnd(msgid, &msg, MSG_SIZE, 0)==-1)
	{
		perror("client: erreur envoi message");
	}

	myanswer_t answer;

	if(msgrcv(msgid, &answer, ANSWER_SIZE, 30, 0)==-1)
	{
		perror("client: erreur reception message");
	}

	printf("client: resultat:%d:\n",answer.result);


	return 0;
}
