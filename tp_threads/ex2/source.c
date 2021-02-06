#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

struct sigaction action;

struct data_s {
    float a;
    float b;
    char op;
};

void *operation(void *arg) {
    int status;

    struct data_s data = *(struct data_s *)arg;
    
    printf("arg:{a=%f;b=%f;op=%d}\n", data.a, data.b, data.op);
    
    if (data.op == 0) {
        int a = (int) data.a;
        int b = (int) data.b;
        printf("%d + %d = %d\n", a, b, a+b);
    } else if (data.op == 1) {
        float a = data.a;
        float b = data.b;
        printf("%f x %f = %f\n", a, b, a*b);
    }

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
