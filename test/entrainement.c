#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_struct {
	int	tab[1];
	pthread_mutex_t mutex;
	pthread_cond_t cond; 
	pthread_cond_t cond1; 
} t_s;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */
pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_cond_t condition1 = PTHREAD_COND_INITIALIZER; /* Création de la condition */


void *ft_thread_1(void *s)
{
	printf("hello\n");
	while (1)
	{
		pthread_mutex_lock(&(((t_s*)s)->mutex));
		pthread_cond_wait(&(((t_s*)s)->cond),&((t_s*)s)->mutex);
		usleep(1000000);
		pthread_cond_signal(&((t_s*)s)->cond1);

		printf("thread 1 %d\n", ((t_s*)s)->tab[0]);
		pthread_mutex_unlock(&(((t_s*)s)->mutex));
		printf("thread 1 apres unlock %d\n", ((t_s*)s)->tab[0]);
	}
	pthread_exit(NULL);
}

void *ft_thread_2(void *s)
{

	printf("yello\n");
	while (1)
		if (((t_s*)s)->tab[0] > 1)
		{
			pthread_mutex_lock(&(((t_s*)s)->mutex));
			((t_s*)s)->tab[0] -= 2;
			printf("thread 2 : je mange %d\n", ((t_s*)s)->tab[0]);
			usleep(1000000);
			pthread_cond_signal(&((t_s*)s)->cond);
			pthread_cond_wait(&(((t_s*)s)->cond1),&((t_s*)s)->mutex);

			pthread_mutex_unlock(&((t_s*)s)->mutex);
			((t_s*)s)->tab[0] += 2;
			printf("thread 2 apres unlock %d\n", ((t_s*)s)->tab[0]);
		}

	pthread_exit(NULL);
}

int main (int ac, char ** av)
{
	pthread_t thread_1;
	pthread_t thread_2;
	t_s s;
	s.tab[0] = 5;
	s.mutex = mutex;
	s.cond = 	condition;
	s.cond1 = 	condition1;
	printf("Avant la création des threads\n");

	if (pthread_create(&thread_1, NULL, ft_thread_1,(void *) &s) ||
			pthread_create(&thread_2, NULL, ft_thread_2,(void *) &s))
		return EXIT_FAILURE;

	if (pthread_join(thread_1, NULL) || pthread_join(thread_2, NULL))
		return EXIT_FAILURE;

	printf("Apres la création des threads\n");
	return EXIT_SUCCESS;
}
