/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:33:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/26 15:04:01 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Returns the result of current_time - past_time. 
*/
size_t	get_time_since(size_t past_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - past_time);
}

/*
Returns the current system time in milliseconds.
*/
size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
Makes current thread sleep for time milliseconds. Sleeps in 0.1ms increments 
until desired total sleep time is reached.
*/
void	time_travel(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(philo->limiter);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->limiter);
	return (last_meal);
}
