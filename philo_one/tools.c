/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:42:06 by adtheus           #+#    #+#             */
/*   Updated: 2021/03/12 17:39:27 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (gettimeofday(start, NULL))
		return (-1);
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
	set_up_sub1(d, start, time_to_stop);
	return (0);
}
