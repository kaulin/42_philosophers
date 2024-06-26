/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:44:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/26 11:30:52 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	release_forks(int forks_grabbed, t_philo *philo)
{
	pthread_mutex_lock(philo->limiter);
	if (forks_grabbed == 1)
	{ 
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->lfork);
		else
			pthread_mutex_unlock(philo->rfork);
	}
	else if (forks_grabbed > 1)
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
	pthread_mutex_unlock(philo->limiter);
}

/*
Makes the specified philosopher lock the specified fork mutex and, once 
successful, prints the appropriate status message.
*/
static int	grab_forks(t_philo *philo)
{
	int	forks_grabbed;

	forks_grabbed = 0;
	if (unsatisfied(philo))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->lfork);
		else
			pthread_mutex_lock(philo->rfork);
		forks_grabbed++;
	}
	if (unsatisfied(philo))
		print_status(philo, "has taken a fork");
	if (unsatisfied(philo))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->rfork);
		else
			pthread_mutex_lock(philo->lfork);
		forks_grabbed++;
	}
	if (unsatisfied(philo))
		print_status(philo, "has taken a fork");
	return (forks_grabbed);
}

/*
Once a philosopher has both forks, they set they set the time of their last 
meal to current time, print eating status, suspend for eating duration, put 
down the forks and if they've reached the meal target, mark themselves as not 
hungry.
*/
void	eat(t_philo *philo)
{
	int	forks_grabbed;

	forks_grabbed = grab_forks(philo);
	if (unsatisfied(philo))
	{
		pthread_mutex_lock(philo->limiter);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->limiter);
		print_status(philo, "is eating");
		time_travel(philo->data->eat_time);
		pthread_mutex_lock(philo->limiter);
		philo->meal_count++;
		if (philo->data->meals && philo->meal_count >= philo->data->meals)
			*philo->hungry = 0;
		pthread_mutex_unlock(philo->limiter);
	}
	release_forks(forks_grabbed, philo);
}

/*
Prints the sleeping status message and suspends the thread for sleep_time ms.
*/
void	nap(t_philo *philo)
{
	print_status(philo, "is sleeping");
	time_travel(philo->data->sleep_time);
}

/*
Prints the thinking status message.
*/
void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
