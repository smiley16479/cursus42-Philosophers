#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int test(void)
{

	for (size_t i = 0; i < 10; ++i)
	{
		usleep(100000);
		printf("i : %d\n", i);
	}
	// return (0);
	exit(1);
}

int main(void)
{
	pthread_t	th;
	pid_t		pid;

// Partie de test pour les thread
	// if (pthread_create(&th, NULL, (void*)test, NULL))
		// return (-1);


	if ((pid = fork()) == -1)
		return (-1);
	else if (pid == 0)
		test();

	// pthread_join(th, NULL);
	printf("est-ce que l'exit quitte slmt le thread ou tout?\n");
	waitpid(pid, NULL, 0);
	printf("est-ce que l'exit quitte slmt le thread ou tout?\n");

	return (0);
}