#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void gestion_sigint(int signumber)
{
	if(signumber == SIGINT)
	{
		printf(MSG);
//		exit(SIGINT);
	}
}

int main(void)
{
	struct sigaction action;
	action.sa_handler = gestion_sigint;
	sigaction(SIGINT, &action, NULL);
	while(1)
		sleep(1);
}
