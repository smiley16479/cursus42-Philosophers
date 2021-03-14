/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phisiology.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:20:13 by adtheus           #+#    #+#             */
/*   Updated: 2021/03/12 20:46:03 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function néccessaires aux thread
*/

float	get_time(struct timeval *start)
{
	struct timeval end;
	float time_taken;

	gettimeofday(&end, NULL);
	time_taken = (end.tv_sec - start->tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start->tv_usec)) * 1e-3;
	// printf("\ntime_taken1 : %.0f\n", time_taken);
	return(time_taken);
}

int	is_phy_dead_or_satiated(t_data *d, struct timeval *start)
{
	int i;
	float	now;

	i = -1;
	now = get_time(start);
	while (++i < d->data[0])
		if ((now - d->tab[i].last_lunch) > d->data[1] / 1000)
		{
			printf("%5.0f %d died\n", (now - d->tab[i].last_lunch), i + 1);
			return (((*d->tab[0].time_to_stop) = 1));
		}
	i = -1;
	if (d->data[4] != -1)
	{
		while (++i < d->data[0])
			if (d->tab[i].lunch_nb < d->data[4])
				break ;
		if (i == d->data[0])
		{
			printf("all phy have eatten %d lunches\n", (*d->tab).lunch_nb);
			return (((*d->tab[0].time_to_stop )= 2));
		}
	}
	return (0);
}

int print_status(char act, t_phy *p)
{
	if (*p->time_to_stop)
		return (1);
	if (act == 1)
		printf("%5.0f %d has taken a fork\n",
		get_time(p->start), p->whoami + 1);
	else if (act == 2)
		printf("%5.0f %d is eating\n", get_time(p->start), p->whoami + 1);
	else if (act == 3)
		printf("%5.0f %d is sleeping\n", get_time(p->start), p->whoami + 1);
	else if (act == 4)
		printf("%5.0f %d is thinking\n", get_time(p->start), p->whoami + 1);
	return (0);
}

void* thread_phy (t_phy *p)
{
	while(1)
	{
		sem_wait(p->sem_l);
		sem_wait(p->sem);
		if (print_status(1, p))
			break ;
		sem_wait(p->sem);
		sem_post(p->sem_l);
		if (print_status(1, p))
			break ;
		if (print_status(2, p))
			break ;
		p->lunch_nb++;
		usleep((*p->data)[2]);
		p->last_lunch = get_time(p->start); // printf("lst_lunch de %d: %f\n",p->whoami + 1, (p->last_lunch = get_time(p->start)));
		sem_post(p->sem);
		sem_post(p->sem);
		if (print_status(3, p))
			break ;
		usleep((*p->data)[3]);
		if (print_status(4, p))
			break ;
	}
	return (NULL);
}
