#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

struct sigaction action;

int pipefd1[2], pipefd2[2], pipefd3[2];

struct data_t {
    int a;
    int b;
    int *pipefd;
};

struct data_t data1, data2, data3;

void *operation1(void *arg) {
    int status;

    struct data_t *data = (struct data_t *) arg;
    int *pipefd = (*data).pipefd;
    int a = (*data).a;
    int b = (*data).b;

    srand(time(NULL));
    int nb = rand() % 11;
    
    int res = a + b + nb;

    write(pipefd[1], &res, sizeof(res));

    close(pipefd[1]);
    
    pthread_exit((void *)&status);
}

void *operation2(void *arg) {
    int status;

    int nb1, nb2, nb3;

    read(pipefd1[0], &nb1, sizeof(nb1));
    read(pipefd2[0], &nb2, sizeof(nb2));
    read(pipefd3[0], &nb3, sizeof(nb3));

    int res = nb1 + nb2 + nb3;
    printf("Result: %d\n", res);

    close(pipefd1[0]);
    close(pipefd2[0]);
    close(pipefd3[0]);

    pthread_exit((void *)&status);
}

void handler(int signal) {
        if (signal == SIGINT){
            printf("SIGINT detected\n");
            
            pthread_t tid4;
            pthread_create(&tid4, NULL, operation2, NULL);

            pthread_join(tid4, NULL);
            
            exit(SIGINT);
        } else {
                // Si erreur
                fprintf(stderr, "Erreur\n");
                exit(-1);
        }
}

int main() {
    if (pipe(pipefd1) != 0) { perror("pipe creation failed!"); return 1; }
    if (pipe(pipefd2) != 0) { perror("pipe creation failed!"); return 1; }
    if (pipe(pipefd3) != 0) { perror("pipe creation failed!"); return 1; }

    data1.a = 4;
    data1.b = 7;
    data1.pipefd = pipefd1;
    
    data2.a = 5;
    data2.b = 1;
    data2.pipefd = pipefd2;
    
    data3.a = 2;
    data3.b = 3;
    data3.pipefd = pipefd3;

    pthread_t tid1;
    pthread_create(&tid1, NULL, operation1, (void *) &data1); 

    pthread_t tid2;
    pthread_create(&tid2, NULL, operation1, (void *) &data2);

    pthread_t tid3;
    pthread_create(&tid3, NULL, operation1, (void *) &data3); 

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Fonction appelée par le signal
    action.sa_handler = handler;
    // Action sur réception SIGINT
    sigaction(SIGINT, &action, NULL);

    pause();
    return 1;
}
