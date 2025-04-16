/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:13:55 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/21 13:13:55 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	ft_atoi(const char *nptr)
{
	long	res;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

long	gettime(long starttime)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000 + (tv.tv_usec) / 1000) - (starttime)));
}

int	mess(char *cause, t_philo *p, long time, int nbr)
{
	if (nbr < 0)
	{
		pthread_mutex_lock(p->print);
		printf("%ld : %d %s\n", time, p->id, cause);
		if (nbr == -2)
			printf("%ld : %d %s\n", time, p->id, cause);
		return (pthread_mutex_unlock(p->print));
	}
	else
	{
		pthread_mutex_lock(p->print);
		printf("%ld : %d %s (%d)\n", time, p->id, cause, nbr);
		return (pthread_mutex_unlock(p->print));
	}
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
