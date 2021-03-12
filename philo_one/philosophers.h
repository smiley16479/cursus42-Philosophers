#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define PML pthread_mutex_lock
#define PMUL pthread_mutex_unlock
enum time {e_nb, e_die, e_eat, e_sleep, e_m_eat};

typedef struct s_phy
{
	int				whoami;
	int				lunch_nb;
	int 			(*data)[5];
	int				*time_to_stop;
	float			last_lunch; // last_lunch
	pthread_t		th_nb; // créer une thread par philosophe
	struct s_phy	*next;
	struct timeval	*start;
	pthread_mutex_t	mutex; // créer un mutex par fourchette
}	t_phy;

/*
** int data[5] --> les arguments :
**	0-	number_of_philosopher
**	1-	time_to_die
**	2-	time_to_eat
**	3-	time_to_sleep
**	4-	[number_of_time_each_philosophers_must_eat]
**
**	t_phy *tab --> le nombre de phy associé à l'argument 1
*/

typedef struct s_data
{
	int		ac;
	char	**av;
	int		data[5];
	t_phy	*tab; // créer autan de thread que de philosophes
}	t_data;

int		ft_atoi(char *str);

/*
** Ds phisiology.c
*/

int		set_up(struct timeval *start, t_data *d, int *time_to_stop);

float	get_time(struct timeval *start);

void	*thread_phy(t_phy *p);

int		is_phy_dead_or_satiated(t_data *d, struct timeval *start);

#endif
