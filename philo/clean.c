/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:25:00 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/19 17:04:10 by jajuntti         ###   ########.fr       */
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