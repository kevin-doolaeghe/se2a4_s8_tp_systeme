#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

static pid_t pid;
static int somme=0;

void gestion_sigterm(int signumber)
{
	printf("Somme: %d\n",somme);
	exit(SIGTERM);
}

void gestion_sigint(int signumber)
{
	if(signumber == SIGINT)
	{
		kill(pid, SIGTERM);
		exit(SIGINT);
	}
}



void fils(void)
{
	struct sigaction action;
	action.sa_handler = gestion_sigterm;
	sigaction(SIGTERM, &action, NULL);

	struct sigaction action_sigint;
	action_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &action_sigint, NULL);

	srand(time(NULL));
	while(1)
	{
		somme += rand()%11;
		sleep(1);
	}
}

int main(void)
{
	pid = fork();
	if(pid == -1)
	{
		perror("Création fils\n");
		exit(1);
	}
	else if(pid == 0)
	{
		fils();
	}
	else
	{
		struct sigaction action;
		action.sa_handler = gestion_sigint;
		sigaction(SIGINT, &action, NULL);
	
		pause();
	}

}
