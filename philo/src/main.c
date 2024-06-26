/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:42 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/26 11:25:43 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Prints a usage message specifying the required arguments.
*/
static int	usage(void)
{
	printf("usage: ./philo number_of_philosophers time_to_die time_to_eat");
	printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (2);
}

/*
Prints "Error: " followed by the message stored in data->error. Then cleans 
the data struct and returns KO (1).
*/
static int	fail(t_data *data)
{
	printf("Error: %s\n", data->error);
	clean_data(data);
	return (KO);
}

/*
Checks the hungry_ones array of integers to see if all the philosophers have 
been fed enough times already. If a hungry philosopher is encountered, returns 
KO (1), else returns OK (1).
*/
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

/*
The monitor loop iterates through the philosopher structs until:
A. All philosophers have eaten at least the number of meals set by the 
optional 5th program argument.
B. The time between meals of one philosopher surpasses the alloted die_time.
*/
static void	monitor(t_data *data)
{
	int		i;
	size_t	last_meal;

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
		last_meal = get_last_meal(&data->philos[i]);
		if (get_time_since(last_meal) > (size_t)data->die_time)
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
	printf("ALERT: all threads joined, cleaning data at %zu!\n", get_time_since(data.start_time));
	clean_data(&data);
	return (OK);
}
