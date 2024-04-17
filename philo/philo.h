/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/17 14:22:21 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int			live_flag;
	int			philo_count;
	size_t		die_time;
	size_t		eat_time;
	size_t		sleep_time;
	int			meal_req;
	t_philo		*philos;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			meal_count;
	int			eating_flag;
	int			dead_flag;
	size_t		start_time;
	size_t		last_meal;
}	t_philo;

#endif