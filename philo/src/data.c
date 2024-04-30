/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:12:25 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/30 14:32:06 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Cleans the data struct, freeing allocated memory and destroying initialized 
mutexes.
*/
void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->seats)
			pthread_mutex_destroy(&data->forks[i++]);
		free (data->forks);
		data->forks = NULL;
	}
	if (data->limiter)
	{
		pthread_mutex_destroy(data->limiter);
		free(data->limiter);
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}

}

static int	check_values(t_data *data)
{
	if (data->seats < 1)
		data->error = "must have at least one philosopher";
	else if (data->seats > 200)
		data->error = "the table only has 200 seats";
	else if (data->die_time < 60 || data->eat_time < 60 \
		|| data->sleep_time < 60)
		data->error = "give philos at least 60ms to sleep/eat/die";
	if (data->error)
		return (KO);
	return (OK);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->seats * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		data->error = "memory allocation error";
		return (KO);
	}
	while (i < data->seats)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
		{
			data->error = "memory allocation error";
			return (KO);
		}
	}
	return (OK);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->seats * sizeof(t_philo));
	if (!data->philos)
	{
		data->error = "memory allocation error";
		return (KO);
	}
	while (i < data->seats)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_count = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].rfork = &data->forks[i];
		if (i == 0)
			data->philos[i].lfork = &data->forks[data->seats - 1];
		else
			data->philos[i].lfork = &data->forks[i - 1];
		data->philos[i].limiter = data->limiter;
		data->philos[i++].data = data;
	}
	return (OK);
}

int	init_data(int argc, char *argv[], t_data *data) 
{
	data->alive = 1;
	data->meal_target = -1;
	data->philos = NULL;
	data->forks = NULL;
	data->error = NULL;
	if (get_int(&data->seats, argv[1]) \
		|| get_int(&data->die_time, argv[2]) \
		|| get_int(&data->eat_time, argv[3]) \
		|| get_int(&data->sleep_time, argv[4]) \
		|| (argc == 6 && get_int(&data->meal_target, argv[5])))
		data->error = "problem parsing arguments";
	data->limiter = malloc(sizeof(pthread_t *));
	if (!data->limiter || pthread_mutex_init(data->limiter, NULL))
		data->error = "memory allocation error";
	if (data->error)	
		return (KO);
	if (check_values(data) || init_forks(data) || init_philos(data))
		return (KO);
	return (OK);
}
