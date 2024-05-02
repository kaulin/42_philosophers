/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:42 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/02 16:44:35 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor(t_data *data)
{
	int	i;

	i = 0;
	while (data->alive_n_hungry)
	{
		if (!all_fed(data))
		{
			pthread_mutex_lock(data->limiter);
			data->alive_n_hungry = 0;
			pthread_mutex_unlock(data->limiter);
			break ;
		}
		if (get_time_since(data->philos[i].last_meal) > (size_t)data->die_time)
		{
			pthread_mutex_lock(data->limiter);
			data->alive_n_hungry = 0;
			pthread_mutex_unlock(data->limiter);
			print_status(&data->philos[i], "died");
			break ;
		}
		if (++i == data->seats)
			i = 0;
	}
}

/*
Philosophers eat, sleep and think. Odd philosophers firs grab their right 
fork, even their left. This prevent's deadlocks.
*/
static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
	{
		think(philo);
		time_travel(10);
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

static int	join_threads(t_data *data)
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

static int	start_threads(t_data *data)
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
		i++;
	}
	return (OK);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (usage());
	if (init_data(argc, argv, &data))
		return (fail(&data));
	if (start_threads(&data))
		return (fail(&data));
	monitor(&data);
	if (join_threads(&data))
		return (fail(&data));
	clean_data(&data);
	return (OK);
}
