/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:12:25 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/19 17:01:54 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
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
			
		}
	}
}

int	init_philos(t_data *data)
{
	int	i;

	i = 1;
	data->philos = malloc(data->seats * sizeof(t_philo));
	if (!data->philos)
	{
		data->error = "memory allocation error";
		return (KO);
	}
	while (i <= data->seats)
	{
		
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
