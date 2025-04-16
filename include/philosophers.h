/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:35:24 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/20 21:35:24 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# define MILLI 1000

typedef struct philo
{
	pthread_mutex_t	*fork;
	pthread_t		philo;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;
	pthread_mutex_t	last_eat_m;
	pthread_mutex_t	n_eat_m;
	int				id;
	long			start_time;
	int				*is_dead;
	int				n_philo;
	int				n_eat;
	int				max_eat;
	int				last_eat;
	int				t_die;
	int				t_eat;
	int				t_sleep;
}						t_philo;

typedef struct param
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	t_philo			*philo;
	pthread_t		brain;
	long			start_time;
	int				is_dead;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
}						t_param;

//init.c
t_param		*create_argument(int argc, char **argv);
pthread_t	create_philo(t_param **tab, int i, char **str);
int			parseur(int argc, char **argv, char **str);

//life.c
long		take_fork(t_philo **p);
void		eat(t_philo **p);
void		drop_fork(t_philo **p);
void		sleep_think_philo(t_philo **p);
void		*life(void *tabe);

//brain.c
int			philo_death_starvation(t_param **p);
int			philo_finish_eat(t_param **p);
void		*brain(void *p);

//utils.c
long		ft_atoi(const char *nptr);
long		gettime(long starttime);
int			mess(char *cause, t_philo *p, long time, int nbr);
int			ft_strstrlen(char **str);
int			ft_strlen(const char *str);
void		ft_usleep(t_philo **p, long start, long time);

//del.c
int			kill(t_philo **p);
int			is_dead(t_philo **p);
void		destroy_mutex(t_param **p);
void		free_split(char **str);
void		free_all(t_param **arg, char **str);

//ft_split.c
char		**ft_split(char *s, char c);

#endif
