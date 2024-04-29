/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:10:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/29 15:39:09 by jajuntti         ###   ########.fr       */
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
		usleep(50);
	pthread_mutex_lock(philo->limiter);
	print_philo(philo);
	pthread_mutex_unlock(philo->limiter);
	while (all_alive(philo->data))
	{
		printf("%d is looking for forks\n", philo->id);
		eat(philo);
		printf("%d is gonna nap after eating\n", philo->id);
		nap(philo);
		printf("%d is awake and ready to think\n", philo->id);
		think(philo);
	}
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		enough_meals;

	data = arg;
	i = 0;
	printf("Monitor started! [x%x]\n", (unsigned int)&data->monitor);
	while (all_alive(data) || enough_meals)
	{
		printf("Monitor checking philo id %d\n", data->philos[i].id);
		enough_meals = 1;
		pthread_mutex_lock(&data->limiter);
		printf("Monitor checking philo id %d mealcount\n", data->philos[i].id);
		if (data->meal_target > 0 && data->philos[i].meal_count < data->meal_target)
			enough_meals = 0;
		printf("Monitor checking philo id %d time since last meal\n", data->philos[i].id);
		if (get_time_since(data->philos[i].last_meal > (size_t)data->die_time))
		{
			print_status(&data->philos[i], "died");
			data->alive = 0;
			pthread_mutex_unlock(&data->limiter);
			break ;
		}
		pthread_mutex_unlock(&data->limiter);
		printf("Monitor done checking philo id %d\n", data->philos[i].id);
		i++;
		if (i == data->seats)
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
