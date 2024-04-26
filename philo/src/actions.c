/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:44:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/26 16:31:14 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo philo)
{
	if (philo.id % 2)
	{
		pthread_mutex_lock(philo.lfork);
		pthread_mutex_lock(philo.lfork);
	}
	else
	{
		pthread_mutex_lock(philo.lfork);
		pthread_mutex_lock(philo.lfork);
	}
	
}

void	sleep(t_philo philo)
{

}

void	think(t_philo philo)
{
	
}
