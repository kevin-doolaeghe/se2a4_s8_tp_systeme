#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#include "pong_msg.h"



int main(void)
{
	int msgid;
	pong_msg_t msg;
	struct timespec t1, t2;

	/* Récupératio de la file de message */
	if((msgid=msgget(KEY, 0666)) == -1)
	{
		perror("Création de la file de message");
		exit(1);
	}


	strcpy(msg.msg, "PING");
	msg.type = 1;
	timespec_get(&t1, TIME_UTC);
	msgsnd(msgid, &msg, MSGSIZE, 0);
	msgrcv(msgid, &msg, MSGSIZE, 2, 0);
	timespec_get(&t2, TIME_UTC);
	printf("Msg reçu. Time:%ld\n",t2.tv_nsec-t1.tv_nsec);
	
	return 0;
}
