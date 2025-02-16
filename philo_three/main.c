/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:19:57 by adtheus           #+#    #+#             */
/*   Updated: 2021/03/14 17:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** number_of_philosopher
** time_to_die
** time_to_eat
** time_to_sleep
** [number_of_time_each_philosophers_must_eat]
*/

#include "philosophers.h"

int		main(int ac, char **av)
{
	t_data			d;
	struct timeval	start;

	memset(&d, 0, sizeof(d));
	d.ac = ac;
	d.av = av;
	if (set_up(&start, &d))
		return (printf("Usage :\nphilosophers must be >= 2\n"
		"if exist, minimum meal is 1\ndecimal numbers aren't allowed\n"));
	if (d.data[4] != -1)
		while (d.data[0]--)
			waitpid(d.tab[d.data[0]].pid, NULL, 0);
	else
		waitpid(-1, NULL, 0);
	kill_process_n_destroy(&d);
	usleep(100000);
	free(d.tab);
	sem_close(d.sem);
	sem_close(d.sem_l);
	return (0);
}

/*
** Function de convertion des paramètres servant au setup (juste en dessous)
*/

int		ft_atoi(char *str)
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

int		set_up_sub1(t_data *d, struct timeval *start, int i)
{
	sem_unlink("sem");
	sem_unlink("sem_l");
	d->sem = sem_open("sem", O_CREAT, 0660, d->data[0]);
	d->sem_l = sem_open("sem_l", O_CREAT, 0660, 1);
	while (++i < d->data[0])
	{
		memset(&d->tab[i], 0, sizeof(d->tab[i]));
		d->tab[i].whoami = i;
		d->tab[i].start = start;
		d->tab[i].data = &d->data;
		d->tab[i].sem = d->sem;
		d->tab[i].sem_l = d->sem_l;
		d->tab[i].d = d;
	}
	i = -1;
	while (++i < d->data[0])
		if ((d->tab[i].pid = fork()) < 0)
			return (1);
		else if (!d->tab[i].pid)
		{
			if (PC(&(d->tab[i].th_nb), NULL, (void*)is, &(d->tab[i])))
				return (-1);
			process_phy(&(d->tab[i]));
		}
	return (0);
}

int		set_up(struct timeval *start, t_data *d)
{
	d->data[e_m_eat] = -1;
	if (!(d->ac == 5 || d->ac == 6))
	{
		write(1, "Wrong arg number\n", 17);
		return (1);
	}
	while (d->ac-- > 1)
		if ((d->data[d->ac - 1] = ft_atoi(d->av[d->ac])) == -1)
			return (-1);
	if (d->data[0] < 2)
	{
		write(1, "Wrong arg format\n", 17);
		return (1);
	}
	d->data[1] *= 1000;
	d->data[2] *= 1000;
	d->data[3] *= 1000;
	d->tab = malloc(d->data[0] * sizeof(t_phy));
	if (gettimeofday(start, NULL))
		return (-1);
	if (set_up_sub1(d, start, -1))
		kill_process_n_destroy(d);
	return (0);
}

int		kill_process_n_destroy(t_data *d)
{
	int i;

	i = -1;
	while (++i < d->data[0])
		kill(d->tab[i].pid, SIGKILL);
	exit(0);
}
