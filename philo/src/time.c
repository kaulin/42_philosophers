/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:33:32 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/30 11:40:52 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_since(size_t past_time)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - past_time);
}

size_t	get_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
