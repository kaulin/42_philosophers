/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:10:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/22 17:39:22 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("Hi, I am Philosopher #%d and my thread id is %zu!\n", philo->id, philo->thread);
	return (NULL);
}

int	start_threads(t_data *data)
{
	int		i;
	t_philo	this;

	i = 0;
	while (i < data->seats)
	{
		this = data->philos[i];
		if (pthread_create(&this.thread, NULL, &routine, &this))
		{
			data->error = "multithreading failed";
			return (KO);
		}
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &routine, data))
	{
		data->error = "multithreading failed";
		return (KO);
	}
}
