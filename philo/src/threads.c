/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:10:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/30 14:53:38 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Philosophers eat, sleep and think. Odd philosophers firs grab their right 
fork, even their left. This prevent's deadlocks.
*/
static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat(philo);
		nap(philo);
		think(philo);
	}
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	i = 0;
	while (data->alive)
	{
		pthread_mutex_lock(data->limiter);
		//if (data->meal_target > 0 && data->philos[i].meal_count < data->meal_target)
		//	enough_meals = 0;
		if (get_time_since(data->philos[i].last_meal) > (size_t)data->die_time)
		{
			data->alive = 0;
			pthread_mutex_unlock(data->limiter);
			print_status(&data->philos[i], "died");
			break ;
		}
		pthread_mutex_unlock(data->limiter);
		if (++i == data->seats)
			i = 0;
	}
	return (NULL);
}

int	join_monitor(t_data *data)
{
	if (pthread_join(data->monitor, NULL))
	{
		data->error = "joining threads failed";
		return (KO);
	}
	return (OK);
}

int	start_threads(t_data *data)
{
	int		i;
	t_philo	*this;

	i = 0;
	data->start_time = get_time();
	while (i < data->seats)
	{
		this = &data->philos[i];
		this->last_meal = data->start_time;
		if (pthread_create(&this->thread, NULL, &philo_routine, this))
			data->error = "multithreading failed";
		if (data->error)
			return (KO);
		if (pthread_detach(data->philos[i].thread))
			data->error = "detaching threads failed";
		if (data->error)
			return (KO);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data))
	{
		data->error = "multithreading failed";
		return (KO);
	}
	return (OK);
}
