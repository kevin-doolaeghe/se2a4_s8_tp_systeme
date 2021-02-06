#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// SIGINT  = Ctrl-C
// SIGQUIT = Ctrl-\
// ps aux | grep program
// kill -3 [pid]

struct sigaction action1, action2;

void print_msg(char *msg) {
	printf(msg);
}

void hand(int sig){
	if (sig == SIGINT){
		// SIGINT
		print_msg("Signal SIGINT reçu");
		exit(SIGINT);
	} else if (sig == SIGQUIT) {
		// SIGQUIT
		print_msg("Signal SIGQUIT reçu");
		exit(SIGQUIT);
	} else {
		// Si erreur
		fprintf(stderr, "Erreur\n");
		exit(-1);
	}
}

int main() {
	// Fonction appelée par le signal
	action1.sa_handler = hand;
	action2.sa_handler = hand;
	// Action sur réception d'un signal
	sigaction(SIGINT, &action1, NULL);
	sigaction(SIGQUIT, &action2, NULL);

	// Boucle infinie
	while (1) sleep(1);
	return 0;
}
