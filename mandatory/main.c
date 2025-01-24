/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:34:17 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/20 21:34:17 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	pthread_t	*philosopher;
	t_param		*arg;
	int			i;
	char		**str;

	str = NULL;
	if (argc == 6)
		str = ft_split(argv[argc - 1], ' ');
	if (parseur(argc, argv, str) != 0)
		return (free_split(str), 1);
	i = -1;
	philosopher = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	arg = create_argument(argc, argv);
	while (++i < ft_atoi(argv[1]))
		philosopher[i] = create_philo(life, &arg, i, str);
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(philosopher[i], NULL);
	free_all(&arg, str, philosopher);
}
