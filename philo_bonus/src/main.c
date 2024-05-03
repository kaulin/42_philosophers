/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:42 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/03 09:44:38 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
The monitor loop iterates through the philosopher structs until:
A. All philosophers have eaten at least the number of meals set by the 
optional 5th program argument.
B. The time between meals of one philosopher surpasses the alloted die_time.
*/
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
Philosophers eat, sleep and think. To prevent deadlocks, even philosophers 
first think and wait for 10ms before trying to grab their left fork. Odd 
philosophers grab their forks right away (right one first) and then start 
eating. This delay and alternate order prevents deadlocks.
*/
static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
	{
		think(philo);
		time_travel(10);
		grab_fork(philo, philo->lfork);
		grab_fork(philo, philo->rfork);
	}
	else
	{
		grab_fork(philo, philo->rfork);
		grab_fork(philo, philo->lfork);
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
Joins the philosopher threads. 
*/
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

/*
Sets the simulation start_time and copies that to the each philosopher's 
last_meal. Then each philosopher thread is started with the corresponding 
philo struct as a parameter.
*/
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

/*
Checks the number of arguments. Initialises data. Starts the philosopher 
threads. Starts monitor loop until end conditions are met. Joins threads. 
Cleans data. Errors are handled after each step.
*/
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
