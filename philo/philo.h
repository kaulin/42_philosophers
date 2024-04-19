/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/19 16:49:21 by jajuntti         ###   ########.fr       */
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

typedef struct s_data
{
	int				dead_flag;
	int				seats;
	int				meal_target;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	char			*error;
}	t_data;

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
	t_philo			*next;
}	t_philo;

// clean.c
void	clean_data(t_data *data);

// init.c
int	init_data(int argc, char *argv[], t_data *data);



#endif