/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:20:23 by adtheus           #+#    #+#             */
/*   Updated: 2021/03/13 12:05:10 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	usleep(100000);
	free(d.tab);
	return 0;
}

/*
** Function basiques
*/

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
	return (nb == 0 ? -1 : nb);
}

/*
** Function de setup
*/

int set_up_sub1(t_data *d, struct timeval *start, int *time_to_stop)
{
	int i;

	i = -1;
	while (++i < d->data[0])
	{
		d->tab[i].whoami = i;
		d->tab[i].lunch_nb = 0;
		d->tab[i].start = start;
		d->tab[i].last_lunch = 0;
		d->tab[i].data = &(d->data);
		d->tab[i].time_to_stop = time_to_stop; // NULL;
		d->tab[i].next = &(d->tab[(i + 1) % d->data[0]]);
		if (pthread_mutex_init(&(d->tab[i].mutex), NULL))
			return (1);
	}
	// printf("%d\n%d\n%f\n", d->tab[0].whoami, (*d->tab).lunch_nb, d->tab[0].last_lunch);
	i = -1;
	while (++i < d->data[0])
	{
		pthread_create(&(d->tab[i].th_nb), NULL, (void*)thread_phy, &(d->tab[i]));
		// pthread_detach(d->tab[i].th_nb);
	}
	return (0);
}

int set_up(struct timeval *start, t_data *d, int *time_to_stop)
{
	d->data[e_m_eat] = -1;
	if (!(d->ac == 5 || d->ac == 6))
	{
		write(1, "Wrong arg number\n", 17);
		return (1);
	}
	while (d->ac-- > 1)
		if ((d->data[d->ac - 1] = (ft_atoi(d->av[d->ac]) * ((d->ac >= 2 && d->ac <= 4) ? 1000 : 1))) == -1)
			return (-1);
	d->tab = malloc(d->data[0] * sizeof(t_phy));
	if (gettimeofday(start, NULL))
		return (-1);
	set_up_sub1(d, start, time_to_stop);
	return (0);
}
