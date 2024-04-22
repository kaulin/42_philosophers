/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/22 17:37:00 by jajuntti         ###   ########.fr       */
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
	char			*error;
}	t_data;

// data.c
void	clean_data(t_data *data);
int		init_data(int argc, char *argv[], t_data *data);

// get_int_from_string.c
int		get_int_from_string(int *dest, char *str);

// threads.c
int		start_threads(t_data *data);

#endif