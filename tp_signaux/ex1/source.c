#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

struct sigaction action;

void hand(int sig){
	if (sig == SIGINT){
		// Si SIG_INT
		printf(MSG);
		exit(SIGINT);
	} else {
		// Si erreur
		fprintf(stderr, "Erreur\n");
		exit(-1);
	}
}

int main() {
	// Fonction appelée par le signal
	action.sa_handler = hand;
	// Action sur réception SIGINT
	sigaction(SIGINT, &action, NULL);

	// Boucle infinie
	while (1) sleep(1);
	return 0;
}
