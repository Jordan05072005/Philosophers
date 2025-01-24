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

int	kill(t_philo **p)
{
	long	time;

	if (*(*p)->is_dead == 1)
		return (1);
	time = gettime(*p);
	if (time >= ((*p)->last_eat + (*p)->t_die))
	{
		*(*p)->is_dead = 1;
		mess("died", (*p)->id, time, -1);
		return (1);
	}
	else if ((*p)->n_eat == (*p)->max_eat)
	{
		*(*p)->is_dead = 1;
		mess("is satisfied", (*p)->id, time, -1);
		return (1);
	}
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
		pthread_mutex_destroy(&(*p)->fork[i]);
}

void	free_all(t_param **arg, char **str, pthread_t *philosopher)
{
	free_split(str);
	destroy_mutex(arg);
	free(philosopher);
	free((*arg)->fork);
	free((*arg)->philo);
	free((*arg));
}
