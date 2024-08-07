/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:33:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/02 09:31:40 by jajuntti         ###   ########.fr       */
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
void	time_travel(size_t time, t_philo *philo)
{
	size_t	start;

	if (time < 1)
		return ;
	start = get_time();
	while (unsatisfied(philo) && get_time() - start < time)
		usleep(100);
}

/*
Returns the time when the specific philo last started eating.
*/
size_t	get_last_meal(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(philo->limiter);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->limiter);
	return (last_meal);
}

/*
Sets the simulation start_time and copies that to the each philosopher's 
last_meal. 
*/
void	set_start_times(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->limiter);
	data->start_time = get_time();
	while (i < data->seats)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	pthread_mutex_unlock(data->limiter);
}
