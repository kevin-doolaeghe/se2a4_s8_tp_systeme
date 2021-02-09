#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Définition des structures pour l'envoi des paramètres au thread */
typedef struct add_value_s {
	int val1;
	int val2;
} add_value_t;

typedef struct mult_value_s {
	float val1;
	float val2;
} mult_value_t;


/* Fonctions "thread" */
void * add(void *arg)
{
	int *result = (int*)malloc(sizeof(int));

	add_value_t args = *(add_value_t *)arg;
	*result = args.val1 + args.val2;

	return result;
}

void * mult(void *arg)
{
	float *result = (float *)malloc(sizeof(float));

	mult_value_t args = *(mult_value_t *)arg;
	*result = args.val1 * args.val2;

	return result;
}

int main(void)
{
	int operation;
	pthread_t tid1;
	add_value_t add_args;
	mult_value_t mult_args;
	
	int *resultat;
	float *f_resultat;

	while(1)
	{
		printf("Veuillez entrer l'opération à réaliser : 1 pour add, 2 pour mult\n");
		scanf("%d", &operation);
		switch(operation)
		{
			case 1:
				printf("entrez les deux valeurs\n");
				scanf("%d %d",&add_args.val1, &add_args.val2);
				pthread_create(&tid1,NULL,add,&add_args);
				pthread_join(tid1,(void **)&resultat);
				printf("valeur: %d\n",*resultat);
				free(resultat);
				break;
			case 2:
				printf("entrez les deux valeurs\n");
				scanf("%f %f",&mult_args.val1, &mult_args.val2);
				pthread_create(&tid1,NULL,mult,&mult_args);
				pthread_join(tid1,(void **)&f_resultat);
				printf("valeur: %f\n",*f_resultat);
				free(f_resultat);
				break;
		}
	}

	return 0;
}
