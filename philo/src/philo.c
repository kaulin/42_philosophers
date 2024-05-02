/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:42 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/02 13:50:39 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	usage(void)
{
	printf("usage: ./philo number_of_philosophers time_to_die time_to_eat");
	printf(" /time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (2);
}

static int	fail(t_data *data)
{
	printf("Error: %s\n", data->error);
	clean_data(data);
	return (KO);
}

static int	all_fed(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->seats)
	{
		if (data->hungry_ones[i])
			return (KO);
		i++;
	}
	return (OK);
}

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
