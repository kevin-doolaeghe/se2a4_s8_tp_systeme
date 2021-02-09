#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void * thread1(void *arg)
{
	*(int *)arg += 500;
	return NULL;
}

void * thread2(void *arg)
{
	*(int *)arg /= 2;
	return NULL;
}

int main(void)
{
	pthread_t tid1, tid2;
	int valeur=100;
	
	pthread_create(&tid1,NULL,thread1,(void *)&valeur);
	pthread_create(&tid2,NULL,thread2,(void *)&valeur);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("valeur: %d\n",valeur);

	return 0;
}
