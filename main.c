/*
number_of_philosopher 
time_to_die 
time_to_eat
time_to_sleep
[number_of_time_each_philosophers_must_eat]
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "philosophers.h"

pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

void* threadAlarme (void* arg);
void* threadCompteur (void* arg);

int ft_atoi(char *str)
{
	int i;
	int nb;

	i = -1;
	nb = 0;
	while (str[++i])
	{
		nb *= 10;
		if (str[i] == '-' || !('0' <= str[i] && str[i] <= '9'))
			return (-1);
		nb += str[i] - '0';
	}
	return (nb);
}

void ft_fork_nb(t_phy *s)
{
	s->time[0] = s->time[0] / 2;
}


void init_stuc(t_phy *s)
{
	int i;

	i = 5;
	while (i--)
		s->time[i] = 0;
}

int main(int ac, char **av)
{
	int i = 0;
	t_phy s;

	init_stuc(&s);
	if (!(ac == 5 || ac == 6))
	{
		write(1, "Wrong arg number\n", 17);
		return (0);
	}
	while (ac-- > 1)
		if ((s.time[ac - 1] = ft_atoi(av[ac])) == -1 )
			return (-1);
	while (i < 5)
		printf("%d\n", s.time[i++]);

/*
	pthread_t monThreadCompteur;
	pthread_t monThreadAlarme;

	pthread_create (&monThreadCompteur, NULL, threadCompteur, (void*)NULL);
	pthread_create (&monThreadAlarme, NULL, threadAlarme, (void*)NULL); // Création des threads 

	pthread_join (monThreadCompteur, NULL);
	pthread_join (monThreadAlarme, NULL); // Attente de la fin des threads 
*/
	return 0;
}

void* threadCompteur (void* arg)
{
	int compteur = 0, nombre = 0;
	
	srand(time(NULL));

	while(1) // Boucle infinie 
	{
		nombre = rand()%10; // On tire un nombre entre 0 et 10 
		compteur += nombre; // On ajoute ce nombre à la variable compteur 

		printf("\n%d", compteur);
		
		if(compteur >= 20) // Si compteur est plus grand ou égal à 20 
		{
			pthread_mutex_lock (&mutex); // On verrouille le mutex 
			pthread_cond_signal (&condition); // On délivre le signal : condition remplie 
			pthread_mutex_unlock (&mutex); // On déverrouille le mutex 

			compteur = 0; // On remet la variable compteur à 0
		}

		sleep (1); // On laisse 1 seconde de repos 
	}
	
	pthread_exit(NULL); // Fin du thread 
}

void* threadAlarme (void* arg)
{
	while(1) // Boucle infinie 
	{
		pthread_mutex_lock(&mutex); // On verrouille le mutex 
		pthread_cond_wait (&condition, &mutex); // On attend que la condition soit remplie 
		printf("\nLE COMPTEUR A DÉPASSÉ 20."); 
		pthread_mutex_unlock(&mutex); // On déverrouille le mutex 
	}
	
	pthread_exit(NULL); // Fin du thread 
}

