/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:12:25 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/26 12:16:19 by jajuntti         ###   ########.fr       */
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
	if (data->philos)
		free(data->philos);
}

/*
Checks that the values parsed from arguments are within acceptable ranges 
and if not, sets a specific error message.
*/
static int	check(t_data *data)
{
	if (data->seats < 1)
		data->error = "must have at least one philosopher";
	else if (data->die_time <= 0 || data->eat_time <= 0 \
		|| data->sleep_time <= 0)
		data->error = "give the philosophers some time do eat, sleep and die";
	else if (data->meals && data->meals < 1)
		data->error = "the philosophers need at least one meal";
	if (data->error)
		return (KO);
	return (OK);
}

/*
Mallocs and initialises one fork mutex per philosopher present at the table. 
Returns an error if mallocing or mutex initialising fails.
*/
int	set_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->seats * sizeof(pthread_mutex_t *));
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
Initialises the given data struct with provided arguments. Converts arguments 
to integers, checks their values, sets the fork mutexes and initialises the 
philo structs.
*/
int	init_data(int argc, char *argv[], t_data *data)
{
	data->alive_n_hungry = 1;
	data->meals = 0;
	data->hungry_ones = NULL;
	data->philos = NULL;
	data->forks = NULL;
	data->error = NULL;
	if (get_int(&data->seats, argv[1]) \
		|| get_int(&data->die_time, argv[2]) \
		|| get_int(&data->eat_time, argv[3]) \
		|| get_int(&data->sleep_time, argv[4]) \
		|| (argc == 6 && get_int(&data->meals, argv[5])))
		data->error = "problem parsing arguments";
	if (check(data))
		return (KO);
	data->limiter = malloc(sizeof(pthread_mutex_t *));
	if (!data->limiter || pthread_mutex_init(data->limiter, NULL))
		data->error = "memory allocation error";
	data->hungry_ones = malloc(data->seats * sizeof(int));
	if (!data->hungry_ones)
		data->error = "memory allocation error";
	if (data->error || set_forks(data) || init_philos(data))
		return (KO);
	return (OK);
}
