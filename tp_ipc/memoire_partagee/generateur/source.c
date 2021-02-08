#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define NB 64
#define CLE (key_t)1000

int main() {
    int shmid, * adr,  i;
    if  ((shmid=shmget  (CLE,  NB*sizeof(int),  IPC_CREAT|IPC_EXCL|0666)) == -1){
        perror("shmget"); exit(2);
    }

    /* attachement à une adresse non fixée */
    if ((adr = (int *) shmat(shmid, 0, 0)) == (int *)(1)) {
        perror("shmat");
        exit(2);
    }
    /* init du générateur de nombre aléatoires */
    srand(getpid());
    /* init du tableau */
    for (i = 0; i < NB; i++)
        printf("%d ", adr[i] = rand() % 100);
    
    putchar("\n");
    
    return 0;
}
