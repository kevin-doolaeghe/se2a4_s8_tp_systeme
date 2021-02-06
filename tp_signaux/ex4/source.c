#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

static struct sigaction action;
// Static pour portée juste sur le fichier
// PID du processus fils
static int fils;
// Somme
static int somme = 0;

void print_msg(char *msg) {
	printf(msg);
}

void hand(int sig){
	if (sig == SIGINT){
		// SIGINT
		print_msg("\nSignal SIGINT reçu\n");

        if (fils == 0) {
            printf("Somme : %d\n", somme);
        } else if (fils > 0) {
            kill(fils, SIGINT);
        }
        
        exit(SIGINT);
	} else {
		// Si erreur
		fprintf(stderr, "Erreur\n");
		exit(-1);
	}
}

int main() {
    fils = fork();

	// Fonction appelée par le signal
    action.sa_handler = hand;
	// Action sur réception d'un signal
    sigaction(SIGINT, &action, NULL);

    /*
     * <0 --> fork failed
     * =0 --> child process
     * >0 --> parent process
     */
    if (fils == 0) {
        srand(time(NULL));

        while (1) {
            somme += rand() % 11;
            sleep(1);
        }
    } else if (fils > 0) {
	    // Boucle infinie
        pause();
    }

	return 0;
}
