/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:44:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/02 09:30:34 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	print_status(t_philo *philo, char *msg)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->limiter);
	timestamp = get_time_since(philo->data->start_time);
	printf("%zums %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(philo->limiter);
}

void	grab_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (philo->data->alive)
		print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		
		grab_fork(philo, philo->lfork);
		grab_fork(philo, philo->rfork);
	}
	else
	{
		grab_fork(philo, philo->rfork);
		grab_fork(philo, philo->lfork);
	}
	if (philo->data->alive)
	{
		pthread_mutex_lock(philo->limiter);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->limiter);
		print_status(philo, "is eating");
		time_travel(philo->data->eat_time);
		pthread_mutex_lock(philo->limiter);
		philo->meal_count++;
		pthread_mutex_unlock(philo->limiter);
		release_forks(philo);
	}
}

void	think(t_philo *philo)
{
	if (philo->data->alive)
		print_status(philo, "is thinking");
}
