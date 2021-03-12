#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */
pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_cond_t condition1 = PTHREAD_COND_INITIALIZER; /* Création de la condition */
int t = 5;  /* data passed to the new thread */

void* thread_1(void* data)
{
	// pthread_join(my_data, NULL);		/* wait for thread tid     */
	// pthread_detach(pthread_self());
	while (1)
	{
		pthread_mutex_lock(&mutex);
		--t;
		printf("Ds thread_1 : data : %d \n", t);
		write(1, "\a", 1);
		pthread_mutex_unlock(&mutex);
		// printf("\nDs thread_1\n");
		usleep(200); /* time to do smthg */
	}

	// pthread_exit(NULL);			/* terminate the thread */
}

void* thread_2(void* data)
{
	// pthread_detach(pthread_self());
	while (1)
	{
		pthread_mutex_lock(&mutex);
		++t;
		usleep(100); /* time to do smthg */
		printf("Ds thread_2 : data : %d \n", t);
		pthread_mutex_unlock(&mutex);
		usleep(10); /* time to do smthg */
	}

	// pthread_exit(NULL);			/* terminate the thread */
}

int main(int ac, char* av[])
{
	(void)ac;
	(void)av;
	int			rc;	/* return value                           */
	pthread_t	thread_id_1;     	/* thread's ID (just an integer)          */
	pthread_t	thread_id_2;     	/* thread's ID (just an integer)          */
	pthread_t	t_main_id = pthread_self(); /* ID de la thread main() */

	rc = pthread_create(&thread_id_1, NULL, thread_1, (void*)t); 
	rc += pthread_create(&thread_id_2, NULL, thread_2, (void*)t); 
	if(rc)			/* could not create thread */
	{
		printf("\n ERROR: return code from pthread_create is %d \n", rc);
		exit(1);
	}
	usleep(1000000);
	while (t <= 10 || t >= 0)
		usleep(1000000);

	// pthread_exit(NULL);		/* terminate the thread */
}