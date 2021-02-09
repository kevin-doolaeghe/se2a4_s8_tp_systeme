#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void * thread1(void *arg)
{
	*(int *)arg;
	*valeur +=500;
	return valeur;
}

void * thread2(void *arg)
{
	int *valeur = (int *)malloc(sizeof(int));
	*valeur = *(int *)arg;
	*valeur = *valeur/2;
	return valeur;
}

int main(void)
{
	pthread_t tid1, tid2;
	int valeur=100;
	int *v1, *v2;
	pthread_create(&tid1,NULL,thread1,(void *)&valeur);
	pthread_create(&tid2,NULL,thread2,(void *)&valeur);
	pthread_join(tid1,(void **)&v1);
	pthread_join(tid2,(void **)&v2);
	printf("v1: %d\n",*v1);
	printf("v2: %d\n",*v2);

	return 0;
}
