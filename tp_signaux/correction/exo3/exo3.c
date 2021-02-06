#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void gestion_sigint(int signumber)
{
	if(signumber == SIGINT)
	{
		sleep(10);
	}
}

int main(void)
{
	struct sigaction action;
	sigset_t sigens;

	sigemptyset(&sigens);
	sigaddset(&sigens, SIGQUIT);

	action.sa_handler = gestion_sigint;
	action.sa_mask = sigens;
	sigaction(SIGINT, &action, NULL);
	
	while(1)
	{
		sleep(1);
		printf("je me réveille\n");
	}
}
