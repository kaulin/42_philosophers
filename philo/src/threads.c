/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:46:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/27 10:49:00 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Waits for the start mutex lock to be opened, so the simulation can start.
*/
static void	wait_while_threads_start(t_philo *philo)
{
	pthread_mutex_lock(philo->data->start_mutex);
	pthread_mutex_unlock(philo->data->start_mutex);
}

/*
Philosophers eat, sleep and think. To prevent deadlocks, even philosophers 
first think and wait for 10ms before trying to grab their left fork. Odd 
philosophers grab their forks right away (right one first) and then start 
eating. This delay and alternate order prevents deadlocks.
*/
static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_while_threads_start(philo);
	if (!unsatisfied(philo))
		return (NULL);
	if (philo->id % 2 == 0)
	{
		think(philo);
		time_travel(3, philo);
	}
	while (unsatisfied(philo))
	{
		if (unsatisfied(philo))
			eat(philo);
		if (unsatisfied(philo))
			nap(philo);
		if (unsatisfied(philo))
			think(philo);
	}
	return (NULL);
}

/*
Philosophers eat, sleep and think. In the case of only one philosopher, that 
one is aware that they only have access to one fork and don't even bother 
picking it up, choosing to think for the last moments of their life.
*/
static void	*hermit_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (unsatisfied(philo))
	{
		think(philo);
		time_travel(philo->data->die_time + 42, philo);
	}
	return (NULL);
}

/*
Joins n number of philosopher threads. 
*/
int	join_threads(int n, t_data *data)
{
	int	i;

	i = 0;
	while (i < n)
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

/*
Each philosopher thread is made with the corresponding 
philo struct as a parameter.
*/
int	make_threads(t_data *data)
{
	int		i;
	t_philo	*this;

	i = 0;
	while (i < data->seats)
	{
		this = &data->philos[i];
		if (data->seats != 1 \
			&& pthread_create(&this->thread, NULL, &philo_routine, this))
			data->error = "multithreading failed";
		if (data->seats == 1 \
			&& pthread_create(&this->thread, NULL, &hermit_routine, this))
			data->error = "multithreading failed";
		if (data->error)
		{
			data->alive_n_hungry = 0;
			join_threads(i, data);
			return (KO);
		}
		i++;
	}
	set_start_times(data);
	return (OK);
}
