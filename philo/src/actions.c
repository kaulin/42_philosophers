/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:44:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/29 15:36:25 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_alive(t_data *data)
{
	int	value;
	
	pthread_mutex_lock(&data->limiter);
	value = data->alive;
	pthread_mutex_unlock(&data->limiter);
	return (value);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	print_status(t_philo *philo, char *msg)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->limiter);
	timestamp = get_time() - philo->data->start_time;
	printf("%zums %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(philo->limiter);
}

void	grab_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (all_alive(philo->data))
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
	if (all_alive(philo->data))
	{
		pthread_mutex_lock(philo->limiter);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->limiter);
		print_status(philo, "is eating");
		usleep(philo->data->eat_time);
		release_forks(philo);
	}
}

void	nap(t_philo *philo)
{
	if (all_alive(philo->data))
	{
		pthread_mutex_lock(philo->limiter);
		printf("%zums %d is sleeping\n", get_time(), philo->id);
		pthread_mutex_unlock(philo->limiter);
		usleep(philo->data->sleep_time);
	}
}

void	think(t_philo *philo)
{
	if (all_alive(philo->data))
		print_status(philo, "is thinking");
}
