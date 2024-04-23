/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:10:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/23 14:52:14 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->start_time = get_time();
	pthread_mutex_lock(philo->print_lock);
	print_philo(philo);
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = arg;
	
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
	return (OK);
}

int	start_threads(t_data *data)
{
	int		i;
	t_philo	*this;

	i = 0;
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
