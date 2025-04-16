/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:56:47 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/22 14:56:47 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	parseur(int argc, char **argv, char **str)
{
	int	i;

	i = -1;
	if (argc != 5 && argc != 6)
		return (write(2, "number argument invalide", 24));
	if (ft_atoi(argv[1]) <= 0)
		return (write(2, "Nous devons avoir au moins un philosopher\n", 42));
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (write(2, "Donner au moins 60 ms\n", 22));
	if (argc == 6 && ft_strstrlen(str) != ft_atoi(argv[1])
		&& ft_strstrlen(str) != 1)
		return (1);
	while (argc == 6 && str[++i])
	{
		if (ft_atoi(str[i]) < 0)
		{
			write(2, "On peut pas manger négativement !\n", 34);
			return (1);
		}
	}
	return (0);
}

pthread_t	create_philo(t_param **tab, int i, char **str)
{
	pthread_t	philo;

	(*tab)->philo[i].id = i;
	(*tab)->philo[i].is_dead = &(*tab)->is_dead;
	(*tab)->philo[i].t_die = (*tab)->t_die;
	(*tab)->philo[i].n_philo = (*tab)->n_philo;
	(*tab)->philo[i].t_eat = (*tab)->t_eat;
	(*tab)->philo[i].t_sleep = (*tab)->t_sleep;
	(*tab)->philo[i].n_eat = 0;
	(*tab)->philo[i].fork = (*tab)->fork;
	(*tab)->philo[i].death = &(*tab)->death;
	(*tab)->philo[i].print = &(*tab)->print;
	pthread_mutex_init(&(*tab)->philo[i].last_eat_m, NULL);
	pthread_mutex_init(&(*tab)->philo[i].n_eat_m, NULL);
	if (!str)
		(*tab)->philo[i].max_eat = -1;
	else if (ft_strstrlen(str) == 1)
		(*tab)->philo[i].max_eat = ft_atoi(str[0]);
	else if (str)
		(*tab)->philo[i].max_eat = ft_atoi(str[i]);
	(*tab)->philo[i].last_eat = 0;
	return ((*tab)->philo[i].philo);
}

t_param	*create_argument(int argc, char **argv)
{
	struct timeval	tv;
	t_param			*arg;
	int				i;

	i = -1;
	arg = malloc(sizeof(t_param));
	gettimeofday(&tv, NULL);
	arg->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	arg->n_philo = ft_atoi(argv[1]);
	arg->fork = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	while (++i < ft_atoi(argv[1]))
		pthread_mutex_init(&arg->fork[i], NULL);
	arg->t_die = ft_atoi(argv[2]);
	arg->t_eat = ft_atoi(argv[3]);
	arg->t_sleep = ft_atoi(argv[4]);
	arg->is_dead = 0;
	pthread_mutex_init(&arg->death, NULL);
	pthread_mutex_init(&arg->print, NULL);
	arg->philo = malloc(arg->n_philo * sizeof(t_philo));
	return (arg);
}

void	ft_usleep(t_philo **p, long start, long time)
{
	while (gettime((*p)->start_time) - start < time && !is_dead(p))
		usleep(5);
}
