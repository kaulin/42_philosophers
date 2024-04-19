/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:42 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/19 16:16:19 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	usage(void)
{
	printf("usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (2);
}

static int fail(t_data *data)
{
	printf("Error: %s\n", data->error);
	clean_data(data);
	return (KO);
}

static void	*philo_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	init_philo(data);
}



int	main(int argc, char *argv[])
{
	t_data	data;
	
	if (argc < 5 || argc > 6)
		return (usage());
	if (init_data(argc, argv, &data))
		return (fail(&data));
	return (OK);
}
