/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:12:25 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/27 10:36:22 by jajuntti         ###   ########.fr       */
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
	if (data->hungry_ones)
		free(data->hungry_ones);
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
	if (data->start_mutex)
	{
		pthread_mutex_destroy(data->start_mutex);
		free(data->start_mutex);
	}
	if (data->philos)
		free(data->philos);
	free(data);
}

/*
Mallocs and initialises one fork mutex per philosopher present at the table. 
Returns an error if mallocing or mutex initialising fails.
*/
int	set_forks(t_data *data)
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

/*
Initialises the s_philo struct. Returns an error if mallocing for the struct 
fails. The hunger status of the philo is linked to the hungry_ones in array 
and the forks to the corresponding mutexes in data->forks.
*/
int	init_philos(t_data *data)
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
		data->philos[i].hungry = &data->hungry_ones[i];
		*data->philos[i].hungry = 1;
		data->philos[i].last_meal = get_time();
		data->philos[i].rfork = &data->forks[i];
		if (data->seats > 1 && i == 0)
			data->philos[i].lfork = &data->forks[data->seats - 1];
		else if (data->seats > 1)
			data->philos[i].lfork = &data->forks[i - 1];
		data->philos[i].limiter = data->limiter;
		data->philos[i++].data = data;
	}
	return (OK);
}

/*
Allocates space for the mutexes within data and initialises them. Returns KO 
on error.
*/
int	init_mutexes(t_data *data)
{
	data->limiter = malloc(sizeof(pthread_mutex_t));
	if (!data->limiter || pthread_mutex_init(data->limiter, NULL))
	{
		data->error = "memory allocation error";
		return (KO);
	}
	data->start_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->start_mutex || pthread_mutex_init(data->start_mutex, NULL))
	{
		data->error = "memory allocation error";
		return (KO);
	}
	return (OK);
}

/*
Initialises the given data struct with provided arguments. Converts arguments 
to integers, checks their values, initialises mutexes and sets up hungry array.
*/
int	init_data(int argc, char *argv[], t_data *data)
{
	data->alive_n_hungry = 1;
	data->meals = 0;
	data->hungry_ones = NULL;
	data->philos = NULL;
	data->forks = NULL;
	data->error = NULL;
	data->limiter = NULL;
	data->start_mutex = NULL;
	if (get_int(&data->seats, argv[1]) || get_int(&data->die_time, argv[2]) \
		|| get_int(&data->eat_time, argv[3]) \
		|| get_int(&data->sleep_time, argv[4]) \
		|| (argc == 6 && get_int(&data->meals, argv[5])))
		data->error = "problem parsing arguments";
	if (check(data) || init_mutexes(data))
		return (KO);
	data->hungry_ones = malloc(data->seats * sizeof(int));
	if (!data->hungry_ones)
		data->error = "memory allocation error";
	if (data->error)
		return (KO);
	return (OK);
}
