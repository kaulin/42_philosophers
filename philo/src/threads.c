/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:10:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/25 09:31:55 by jajuntti         ###   ########.fr       */
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
	if (philo->id % 2)
		usleep(100);
	pthread_mutex_lock(philo->print_lock);
	print_philo(philo);
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	while (!data->dead_flag)
	{
		i = 0;
		while (i < data->seats)
		{
			if (data->philos[i].dead_flag);
		}
		i++;
	}
	return (NULL);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->seats)
	{
		if (pthread_join(data->philos[i].thread, NULL))
		{
			data->error = "joining threads failed";
			return (KO);
		}
		i++;
	}
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
		if (pthread_create(&this->thread, NULL, &philo_routine, this))
		{
			data->error = "multithreading failed";
			return (KO);
		}
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data))
	{
		data->error = "multithreading failed";
		return (KO);
	}
	return (OK);
}
