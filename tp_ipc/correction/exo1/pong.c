#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "pong_msg.h"


static int msgid;

void gestion_sigint(int sig)
{
	printf("Réception du signal SIGINT\n");
	msgctl(msgid, IPC_RMID, NULL);
	exit(SIGINT);
}

int main(void)
{
	pong_msg_t msg;

	/* Création de la file de message */
	if((msgid=msgget(KEY, IPC_CREAT|IPC_EXCL|0666)) == -1)
	{
		perror("Création de la file de message");
		exit(1);
	}

	struct sigaction action;
	action.sa_handler = gestion_sigint;
	sigaction(SIGINT, &action, NULL);

	while(1)
	{
		msgrcv(msgid, &msg, MSGSIZE, 1, 0);
		strcpy(msg.msg, "PONG");
		msg.type = 2;
		msgsnd(msgid, &msg, MSGSIZE, 0);
	}	

	return 0;
}
