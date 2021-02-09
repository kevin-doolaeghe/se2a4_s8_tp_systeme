#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include "serveur.h"

static int msgid;

void intercepteur(int signalNumber)
{
	if(signalNumber == SIGINT)
	{
		printf("Fin de serveur\n");
		msgctl(msgid, IPC_RMID,0);
		exit(SIGINT);
	}
}

void * addition(void *arg)
{
	int * result = (int *)malloc(sizeof(int));
	mymsg_t msg = *((mymsg_t *)arg);
	*result = msg.a+msg.b;
	printf("addition:result:%d:\n",*result);
	return result;
}

void * multiplication(void *arg)
{
	int * result = (int *)malloc(sizeof(int));
	mymsg_t msg = *(mymsg_t *)arg;
	*result = msg.a*msg.b;
	printf("Result:%d:\n",*result);
	return result;
}

int main(void)
{
	struct sigaction action;

	action.sa_handler = intercepteur;
	sigaction(SIGINT, &action, NULL);


	if((msgid = msgget(CLE_MSG,IPC_CREAT|IPC_EXCL|0600))==-1)
	{
		perror("creation file de message");
		exit(1);
	}

	while(1)
	{
		pthread_t tid;
		mymsg_t *msg = (mymsg_t *)malloc(sizeof(mymsg_t));
		int* result = (int *)malloc(sizeof(int));

		if(msgrcv(msgid, msg, MSG_SIZE, -20, 0)==-1)
		{
			perror("Serveur: erreur reception message");
		}
		
		printf("Serveur: message recu:%ld:\n",msg->type);
		switch(msg->type)
		{
			case 10:
				pthread_create(&tid, NULL, addition, (void *)msg);
				pthread_join(tid, (void *)&result);
				break;
			case 20:
				pthread_create(&tid, NULL, multiplication, (void *)msg);
				pthread_join(tid, (void *)&result);
				break;
		}
		myanswer_t answer;
		answer.type = 30;
		answer.result = *result;
		printf("Result:%d:\n",*result);
		free(result);

		if(msgsnd(msgid, &answer, ANSWER_SIZE, 0)==-1)
		{
			perror("Serveur: erreur envoi message");
		}
	}

	return 0;
}
