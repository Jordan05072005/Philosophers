/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:52:22 by jguaglio          #+#    #+#             */
/*   Updated: 2025/04/16 20:52:22 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_finish_eat(t_param **p)
{
	int	i;

	i = -1;
	while (++i < (*p)->n_philo)
	{
		pthread_mutex_lock(&(*p)->philo[i].n_eat_m);
		if ((*p)->philo[i].n_eat == (*p)->philo[i].max_eat)
		{
			pthread_mutex_unlock(&(*p)->philo[i].n_eat_m);
			pthread_mutex_lock((*p)->philo[i].death);
			*(*p)->philo[i].is_dead = 1;
			pthread_mutex_unlock((*p)->philo[i].death);
			mess("is satified", &(*p)->philo[i],
				gettime((*p)->philo[i].start_time), -1);
			return (1);
		}
		pthread_mutex_unlock(&(*p)->philo[i].n_eat_m);
	}
	return (0);
}

int	philo_death_starvation(t_param **p)
{
	int		i;
	long	time;

	i = -1;
	while (++i < (*p)->n_philo)
	{
		time = gettime((*p)->start_time);
		pthread_mutex_lock(&(*p)->philo[i].last_eat_m);
		if (time > (*p)->philo[i].last_eat + (*p)->t_die)
		{
			pthread_mutex_unlock(&(*p)->philo[i].last_eat_m);
			pthread_mutex_lock((*p)->philo[i].death);
			*(*p)->philo[i].is_dead = 1;
			pthread_mutex_unlock((*p)->philo[i].death);
			mess("died", &(*p)->philo[i], time, -1);
			return (1);
		}
		pthread_mutex_unlock(&(*p)->philo[i].last_eat_m);
	}
	return (0);
}

void	*brain(void *tab)
{
	t_param			*p;
	struct timeval	tv;

	p = (t_param *)tab;
	gettimeofday(&tv, NULL);
	p->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (1)
	{
		if (philo_death_starvation(&p) || philo_finish_eat(&p))
			return (NULL);
	}
	return (NULL);
}
