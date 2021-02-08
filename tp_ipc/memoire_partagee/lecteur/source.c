#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define NB 64
#define CLE (key_t) 1000

int main() {
    int shmid, *adr, i;
    if (( shmid = shmget (CLE, NB * sizeof(int), 0666)) == 1) {
        perror ("shmget");
        exit(2);
    }
    
    if (( adr = shmat(shmid, 0, SHM_RDONLY) == (int *)(1))) {
        perror("shmat");
        exit(2);
    }

    for (i = 0; i < NB; i++) {
        printf("%d ", adr[i]);
    }

    putchar("\n");
    
    return 0;
}
