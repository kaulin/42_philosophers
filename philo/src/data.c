/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:12:25 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/22 17:26:34 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
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
	while (i <= data->seats)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_count = 0;
		data->philos[i].eating_flag = 0;
		data->philos[i].dead_flag = 0;
		data->philos[i].start_time = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].rfork = &data->forks[i];
		if (i == 0)
			data->philos[i].lfork = &data->forks[data->seats - 1];
		else
			data->philos[i].lfork = &data->forks[i - 1];
		data->philos[i].last_meal = 0;
	}
}

int	init_data(int argc, char *argv[], t_data *data)
{
	data->dead_flag = 0;
	data->meal_target = -1;
	data->philos = NULL;
	data->error = NULL;
	if (get_int_from_string(&data->seats, argv[1]) \
		|| get_int_from_string(&data->die_time, argv[2]) \
		|| get_int_fromstring(&data->eat_time, argv[3]) \
		|| get_int_fromstring(&data->sleep_time, argv[4]) \
		|| (argc == 6 && get_int_fromstring(&data->meal_target, argv[5])))
	{
		data->error = "problem parsing arguments";
		return (KO);
	}
	if (init_forks(data) || init_philos(data))
		return (KO);
	return (OK);
}
