/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:08:34 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/24 15:08:34 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// int	kill(t_philo **p)
// {
// 	long	time;

// 	//printf("check death for %d at %ld\n", (*p)->id, gettime(*p));
// 	time = gettime(*p);
// 	if (is_dead(p))
// 		return (1);
// 	if (time >= ((*p)->last_eat + (*p)->t_die))
// 	{
// 		pthread_mutex_lock((*p)->death);
// 		*(*p)->is_dead = 1;
// 		pthread_mutex_unlock((*p)->death);
// 		mess("died", p, time, -1);
// 		return (1);
// 	}
// 	else if ((*p)->n_eat == (*p)->max_eat)
// 	{
// 		pthread_mutex_lock((*p)->death);
// 		*(*p)->is_dead = 1;
// 		pthread_mutex_unlock((*p)->death);
// 		mess("is satisfied", p, time, -1);
// 		((*p)->death);
// 		return (1);
// 	}
// 	return (0);
// }

int	is_dead(t_philo **p)
{
	pthread_mutex_lock((*p)->death);
	if (*(*p)->is_dead == 1)
	{
		pthread_mutex_unlock((*p)->death);
		return (1);
	}
	pthread_mutex_unlock((*p)->death);
	return (0);
}

void	free_split(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	destroy_mutex(t_param **p)
{
	int	i;

	i = -1;
	while (++i < (*p)->philo[0].n_philo)
	{
		pthread_mutex_destroy(&(*p)->fork[i]);
		pthread_mutex_destroy(&(*p)->philo[i].last_eat_m);
		pthread_mutex_destroy(&(*p)->philo[i].n_eat_m);
	}
	pthread_mutex_destroy(&(*p)->death);
	pthread_mutex_destroy(&(*p)->print);
}

void	free_all(t_param **arg, char **str)
{
	free_split(str);
	destroy_mutex(arg);
	free((*arg)->fork);
	free((*arg)->philo);
	free((*arg));
}
