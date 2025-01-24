/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:58:55 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/21 16:58:55 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_fork(t_philo **p)
{
	if (kill(p) || (*p)->n_philo == 1)
		return ;
	pthread_mutex_lock(&(*p)->fork[(*p)->id]);
	if (kill(p))
		return (drop_fork(p));
	pthread_mutex_lock(&(*p)->fork[((*p)->id + 1)
		* ((*p)->id != ((*p)->n_philo - 1))]);
	if (kill(p))
		return (drop_fork(p));
	mess("has take a fork", (*p)->id, gettime(*p), -1);
}

void	eat(t_philo **p)
{
	long	time;

	if (*(*p)->is_dead == 1 || (*p)->n_philo == 1)
		return (drop_fork(p));
	time = gettime(*p);
	(*p)->last_eat = time;
	mess("is eating", (*p)->id, time, ++(*p)->n_eat);
	usleep((*p)->t_eat * MILLI);
	drop_fork(p);
	if (*(*p)->is_dead != 1 && (*p)->n_eat != (*p)->max_eat)
		sleep_think_philo(p);
	else
		kill(p);
}

void	drop_fork(t_philo **p)
{
	pthread_mutex_unlock(&(*p)->fork[(*p)->id]);
	pthread_mutex_unlock(&(*p)->fork[((*p)->id + 1)
		* ((*p)->id != (*p)->n_philo - 1)]);
}

void	sleep_think_philo(t_philo **p)
{
	long	sleep;

	sleep = (*p)->t_sleep * MILLI;
	if ((*p)->last_eat + (*p)->t_sleep > (*p)->last_eat + (*p)->t_die)
		sleep = (*p)->t_die * MILLI;
	mess("is sleeping", (*p)->id, gettime(*p), -1);
	usleep(sleep);
	if (!kill(p) && gettime(*p) < ((*p)->last_eat + ((*p)->t_die - 6)))
	{
		mess("is thinking", (*p)->id, gettime(*p), -1);
		usleep((((*p)->last_eat + ((*p)->t_die - 6)) - gettime(*p)) * 1000);
	}
}

void	*life(void *tabe)
{
	struct timeval	tv;
	t_philo			*tab;

	tab = (t_philo *)tabe;
	gettimeofday(&tv, NULL);
	tab->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (*tab->is_dead == 0)
	{
		take_fork(&tab);
		eat(&tab);
	}
	return (NULL);
}
