#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void gestion_sigint(int signumber)
{
	if(signumber == SIGINT)
	{
		printf("SIGINT\n");
		exit(SIGINT);
	}
	else if(signumber == SIGQUIT)
	{
		printf("SIGQUIT\n");
		exit(SIGQUIT);
	}
}

int main(void)
{
	struct sigaction action;
	action.sa_handler = gestion_sigint;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	while(1)
		sleep(1);
}
