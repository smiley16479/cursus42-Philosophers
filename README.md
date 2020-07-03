compilation : gcc -lpthread main.c -o monProgramme

#include <pthread.h>


Manipulation des threads :
****************
int pthread_create(pthread_t * thread, pthread_attr_t * attr,
		   void *(*start_routine) (void *), void *arg);
****************

Supprimer un thread
****************
void pthread_exit(void *ret); // est le return du thread
****************

Attendre la fin d'un thread
 En paramètre l'identifiant du thread et son second paramètre,
 un pointeur, permet de récupérer la valeur retournée par la fonction
 dans laquelle s'exécute le thread (c'est-à-dire l'argument de pthread_exit).
****************
int pthread_join(pthread_t th, void **thread_return);
****************

Les mutex sont en C une variable de type pthread_mutex_t. 
Ils vont nous servir de verrou, pour nous permettre de protéger des données. 
Ce verrou peut donc prendre deux états : disponible et verrouillé. 

Le problème, c'est qu'il faut que le mutex soit accessible en 
même temps que la variable et dans tout le fichier pour cela on peut
déclarer le mutex dans une structure avec la donnée à protéger.

Initialiser un mutex

Conventionnellement, on initialise un mutex avec la valeur 
de la constante PTHREAD_MUTEX_INITIALIZER, déclarée dans pthread.h.
****************
typedef struct data {
    int var;
    pthread_mutex_t mutex;
} data;

int main(void)
{
    data new_data;
    new_data.mutex = PTHREAD_MUTEX_INITIALIZER;
    return EXIT_SUCCESS;
}
****************

Verrouiller un mutex

L'étape suivante consiste à établir une zone critique, c'est-à-dire 
la zone où plusieurs threads ont l'occasion de modifier ou de lire
une même variable en même temps.
Une fois cela fait, on verrouille le mutex grâce à la fonction :
****************
int pthread_mutex_lock(pthread_mutex_t *mut);
****************

Déverrouiller un mutex
A la fin de la zone critique, il suffit de déverrouiller le mutex.
****************
int pthread_mutex_unlock(pthread_mutex_t *mut);
****************

Détruire un mutex
Une fois le travail du mutex terminé, on peut le détruire :
****************
int pthread_mutex_destroy(pthread_mutex_t *mut);
****************

Les conditions

Lorsqu'un thread doit patienter jusqu'à ce qu'un événement survienne 
dans un autre thread, on emploie une technique appelée la condition.
Quand un thread est en attente d'une condition, il reste bloqué tant 
que celle-ci n'est pas réalisée par un autre thread.

Comme avec les mutex, on déclare la condition en variable globale,
de cette manière :
****************
pthread_cond_t nomCondition = PTHREAD_COND_INITIALIZER;
****************

Pour attendre une condition, il faut utiliser un mutex :
****************
int pthread_cond_wait(pthread_cond_t *nomCondition, pthread_mutex_t *nomMutex);
****************

Pour réveiller un thread en attente d'une condition, on utilise la fonction :
****************
int pthread_cond_signal(pthread_cond_t *nomCondition);
****************


Condition du sujet Philosophers:

 number_of_philosopher
 time_to_die
 time_to_eat
 time_to_sleep 
 [number_of_time_each_philosophers_must_eat]

Ils doivent , dans cet ordre :
 manger --> dormir --> penser

