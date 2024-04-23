/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/23 14:46:27 by jajuntti         ###   ########.fr       */
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

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meal_count;
	int				eating_flag;
	int				dead_flag;
	size_t			start_time;
	size_t			last_meal;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*print_lock;
}	t_philo;

typedef struct s_data
{
	int				dead_flag;
	int				seats;
	int				meal_target;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	char			*error;
}	t_data;

// data.c
void	clean_data(t_data *data);
int		init_data(int argc, char *argv[], t_data *data);

// get_int_from_string.c
int		get_int(int *dest, char *str);

// threads.c
int		join_threads(t_data *data);
int		start_threads(t_data *data);

// time.c
size_t	get_time_since(size_t start_time);
size_t	get_time(void);

// utils.c
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);
void	print_data(t_data *data);
void	print_philo(t_philo *philo);

#endif