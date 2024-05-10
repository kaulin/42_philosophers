/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:46:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/10 09:38:05 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Philosophers eat, sleep and think. To prevent deadlocks, even philosophers 
first think and wait for 10ms before trying to grab their left fork. Odd 
philosophers grab their forks right away (right one first) and then start 
eating. This delay and alternate order prevents deadlocks.
*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
	{
		think(philo);
		time_travel(1);
	}
	while (philo->data->alive_n_hungry)
	{
		if (philo->data->alive_n_hungry)
			eat(philo);
		if (philo->data->alive_n_hungry)
			nap(philo);
		if (philo->data->alive_n_hungry)
			think(philo);
	}
	return (NULL);
}

/*
Philosophers eat, sleep and think. In the case of only one philosopher, that 
one is aware that they only have access to one fork and don't even bother 
picking it up, choosing to think for the last moments of their life.
*/
void	*hermit_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->data->alive_n_hungry)
	{
		think(philo);
		time_travel(philo->data->die_time + 42);
	}
	return (NULL);
}

/*
Joins the philosopher threads. 
*/
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

/*
Sets the simulation start_time and copies that to the each philosopher's 
last_meal. Then each philosopher thread is started with the corresponding 
philo struct as a parameter.
*/
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
		if (data->seats != 1 \
			&& pthread_create(&this->thread, NULL, &philo_routine, this))
			data->error = "multithreading failed";
		if (data->seats == 1 \
			&& pthread_create(&this->thread, NULL, &hermit_routine, this))
			data->error = "multithreading failed";
		if (data->error)
			return (KO);
		i++;
	}
	return (OK);
}
