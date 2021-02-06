#include <stdio.h>
#include <pthread.h>

int arg1 = 1, arg2 = 2;
int global;

void *fun_th1(void *arg) {
    int status;
    int num = *(int *)arg;
    printf("hello de thread %d\n", num);
    
    global += 500;
    printf("Global (thread 1) = %d\n", global);

    pthread_exit((void *)&status);
}

void *fun_th2(void *arg) {
    int status;
    int num = *(int *)arg;
    printf("hello de thread %d\n", num);
    
    global /= 2;
    printf("Global (thread 2) = %d\n", global);
    
    pthread_exit((void *)&status);
}

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, fun_th1, (void *) &arg1);
    pthread_create(&tid2, NULL, fun_th2, (void *) &arg2);
    
    printf("j'attends la fin de tid1 et tid2\n");
    pthread_join(tid1, NULL);
    printf("tid1 est terminé\n");
    pthread_join(tid2, NULL);
    printf("fin du programme principal");
}
