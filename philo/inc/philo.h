/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/26 15:34:35 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef OK
#  define OK 0
# endif

# ifndef KO
#  define KO -1
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meal_count;
	int				*hungry;
	size_t			last_meal;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*limiter;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				alive_n_hungry;
	int				seats;
	int				meals;
	int				*hungry_ones;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	size_t			start_time;
	t_philo			*philos;
	pthread_mutex_t	*limiter;
	pthread_mutex_t	*forks;
	char			*error;
}	t_data;

// actions.c
void	eat(t_philo *philo);
void	nap(t_philo *philo);
void	think(t_philo *philo);

// data.c
void	clean_data(t_data *data);
int		init_data(int argc, char *argv[], t_data *data);

// get_int_from_string.c
int		get_int(int *dest, char *str);

// threads.c
void	*philo_routine(void *arg);
void	*hermit_routine(void *arg);
int		join_threads(int n, t_data *data);
int		start_threads(t_data *data);

// time.c
size_t	get_time_since(size_t start_time);
size_t	get_time(void);
void	time_travel(size_t time, t_philo *philo);
size_t	get_last_meal(t_philo *philo);

// utils.c
void	print_status(t_philo *philo, char *msg);
int		unsatisfied(t_philo *philo);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);

#endif