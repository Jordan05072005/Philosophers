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

long	take_fork(t_philo **p)
{
	long	time;
	int		right;

	if ((*p)->n_philo == 1 || is_dead(p))
		return (-1);
	right = ((*p)->id + 1) % (*p)->n_philo;
	if ((*p)->id % 2 == 0)
	{
		pthread_mutex_lock(&(*p)->fork[(*p)->id]);
		pthread_mutex_lock(&(*p)->fork[right]);
	}
	else
	{
		pthread_mutex_lock(&(*p)->fork[right]);
		pthread_mutex_lock(&(*p)->fork[(*p)->id]);
	}
	time = gettime((*p)->start_time);
	if (is_dead(p))
	{
		drop_fork(p);
		return (-1);
	}
	mess("has taken a fork", *p, time, -2);
	return (time);
}

void	eat(t_philo **p)
{
	long	time;

	time = take_fork(p);
	if (time == -1)
		return ;
	pthread_mutex_lock(&(*p)->last_eat_m);
	(*p)->last_eat = time;
	pthread_mutex_unlock(&(*p)->last_eat_m);
	pthread_mutex_lock(&(*p)->n_eat_m);
	mess("is eating", *p, time, ++(*p)->n_eat);
	pthread_mutex_unlock(&(*p)->n_eat_m);
	ft_usleep(p, time, (*p)->t_eat);
	drop_fork(p);
	if (!is_dead(p))
		sleep_think_philo(p);
}

void	drop_fork(t_philo **p)
{
	int	right;
	int	left;

	right = ((*p)->id + 1) % (*p)->n_philo;
	left = (*p)->id;
	if ((*p)->id % 2 == 0)
	{
		pthread_mutex_unlock(&(*p)->fork[left]);
		pthread_mutex_unlock(&(*p)->fork[right]);
	}
	else
	{
		pthread_mutex_unlock(&(*p)->fork[right]);
		pthread_mutex_unlock(&(*p)->fork[left]);
	}
}

void	sleep_think_philo(t_philo **p)
{
	long	time;

	time = gettime((*p)->start_time);
	mess("is sleeping", *p, time, -1);
	ft_usleep(p, time, (*p)->t_sleep);
	if (is_dead(p))
		return ;
	time = gettime((*p)->start_time);
	mess("is thinking", *p, time, -1);
}

void	*life(void *tabe)
{
	struct timeval	tv;
	t_philo			*tab;

	tab = (t_philo *)tabe;
	gettimeofday(&tv, NULL);
	tab->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_lock(&tab->last_eat_m);
	tab->last_eat = gettime(tab->start_time);
	pthread_mutex_unlock(&tab->last_eat_m);
	while (!is_dead(&tab))
		eat(&tab);
	return (NULL);
}
