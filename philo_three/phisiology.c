/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phisiology.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:20:13 by adtheus           #+#    #+#             */
/*   Updated: 2021/03/14 17:45:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function néccessaires aux thread
*/

float	get_time(struct timeval *start)
{
	struct timeval	end;
	float			time_taken;

	gettimeofday(&end, NULL);
	time_taken = (end.tv_sec - start->tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start->tv_usec)) * 1e-3;
	return (time_taken);
}

int		is(t_phy *p)
{
	float	now;

	while (1)
	{
		now = get_time(p->start);
		if ((now - p->last_lunch) > (*p->data)[1] / 1000)
		{
			printf("%5.0f %d died\n", now, p->whoami + 1);
			kill_process_n_destroy(p->d);
		}
		if ((*p->data)[4] != -1)
			if (p->lunch_nb >= (*p->data)[4])
			{
				p->time_to_stop = 1;
				return (0);
			}
	}
	return (0);
}

int		print_status(char act, t_phy *p)
{
	if (p->time_to_stop)
		exit(1);
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

void	*process_phy(t_phy *p)
{
	while (1)
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
		p->last_lunch = get_time(p->start);
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
