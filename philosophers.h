#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

enum time {e_nb, e_die, e_eat, e_sleep, e_m_eat};

typedef struct s_phy
{
	int time[5];
	pthread_t *th_nb; // créer autan de thread que de philosophes
	


}	t_phy;

#endif
