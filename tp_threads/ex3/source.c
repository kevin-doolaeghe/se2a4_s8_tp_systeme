#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct sigaction action;

struct data_s {
    float a;
    float b;
};

void *operation(void *arg) {
    int status;

    int a = ((int *) arg)[0];
    int b = ((int *) arg)[1];
    
    srand(time(NULL));
    int nb = rand() % 11;
    
    status = a + b + nb;

    pthread_exit((void *)&status);
}

void handler(int signal) {
        if (signal == SIGINT){
            printf("SIGINT detected\n");
            exit(SIGINT);
        } else {
                // Si erreur
                fprintf(stderr, "Erreur\n");
                exit(-1);
        }
}

int main() {
    struct data_s data;

    // Fonction appelée par le signal
    action.sa_handler = handler;
    // Action sur réception SIGINT
    sigaction(SIGINT, &action, NULL);

    while (1) {
        printf("Enter nb a :");
        scanf("%f", &(data.a));

        printf("Enter nb b :");
        scanf("%f", &(data.b));
    
        printf("Enter operation (0=plus; 1=mult) :");
        scanf("%d", (int *) &(data.op));
    
        pthread_t tid1;
        pthread_create(&tid1, NULL, operation, (void *) &data); 
        pthread_join(tid1, NULL);
    }
}
