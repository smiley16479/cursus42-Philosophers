/*
number_of_philosopher 
time_to_die 
time_to_eat
time_to_sleep
[number_of_time_each_philosophers_must_eat]
*/

#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	d;
	struct	timeval start;
	int		time_to_stop;

	memset(&d, 0, sizeof(d));
	d.ac = ac;
	d.av = av;
	time_to_stop = 0;
	if (set_up(&start, &d, &time_to_stop))
		return (printf("Usage :\nphilosophers must be >= 2\n"
		"if exist, minimum meal is 1\ndecimal numbers aren't allowed\n"));
	while (!is_phy_dead_or_satiated(&d, &start))
		;
	*(d.tab[0].time_to_stop) = 1;
	// usleep(100);
	// free(d.tab);
	return 0;
	// pthread_exit(NULL);
}

