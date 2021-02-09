#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

typedef struct args_add_s {
	int val1;
	int val2;
	int fd;
} args_add_t;

static int final_result=0;

void sigint_handler(int sig)
{
	printf("Résultat final:%d\n",final_result);
	exit(SIGINT);
}

void * add_push(void *arg)
{
	args_add_t args = *(args_add_t *)arg;
	while(1)
	{
		int result = args.val1 + args.val2 + (rand()%10);
		write(args.fd, &result, sizeof(int));
		sleep(1);
	}
	return NULL;
}

void * add_result(void *arg)
{
	int fd = *(int *)arg;
	int result;

	while(1)
	{
		read(fd,&result,sizeof(int));
		final_result += result;
	}
}

int main(void)
{
	int fd[2];
	args_add_t args1, args2, args3;
	pthread_t tid1, tid2, tid3, tid4;
	pthread_attr_t attr;
	struct sigaction action;

	action.sa_handler = sigint_handler;
	sigaction(SIGINT, &action, NULL);

	if(pipe(fd) == -1)
	{
		perror("Erreur creation tube");
		exit(1);
	}

	srand(time(NULL));

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	args1.val1 = 2;
	args1.val2 = 3;
	args1.fd = fd[1];
	pthread_create(&tid1, &attr, add_push, &args1);

	args2.val1 = 7;
	args2.val2 = 2;
	args2.fd = fd[1];
	pthread_create(&tid2, &attr, add_push, &args2);

	args3.val1 = 9;
	args3.val2 = 5;
	args3.fd = fd[1];
	pthread_create(&tid3, &attr, add_push, &args3);

	pthread_create(&tid4, &attr, add_result, &fd[0]);

	pause();

	return 0;
}
