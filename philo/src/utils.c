/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:42:40 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/27 10:23:24 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Checks that the values parsed from arguments are within acceptable ranges 
and if not, sets a specific error message.
*/
int	check(t_data *data)
{
	if (data->seats < 1)
		data->error = "must have at least one philosopher";
	else if (data->die_time < 0 || data->eat_time < 0 \
		|| data->sleep_time < 0)
		data->error = "times need to be between 0 and 2147483647";
	else if (data->meals && data->meals < 1)
		data->error = "the philosophers need at least one meal";
	if (data->error)
		return (KO);
	return (OK);
}

/*
Prints the provided message preceded by the time in milliseconds passed since 
simulation start and the id number of the philosopher.
*/
void	print_status(t_philo *philo, char *msg)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->data->limiter);
	timestamp = get_time_since(philo->data->start_time);
	if (philo->data->alive_n_hungry || *msg == 'd')
		printf("%zu %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(philo->data->limiter);
}

/*
Returns 1 if all the philosophers are still alive and at least one of them is 
hungry. Otherwise returns 0.
*/
int	unsatisfied(t_philo *philo)
{
	int	satisfaction;

	satisfaction = 1;
	pthread_mutex_lock(philo->data->limiter);
	if (!philo->data->alive_n_hungry)
		satisfaction = 0;
	pthread_mutex_unlock(philo->data->limiter);
	return (satisfaction);
}

/*
Returns a pointer to the first occurence of the character c in string s. If 
s does not contain c, returns NULL.
*/
char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	ch;
	int				i;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == ch)
		return ((char *)&str[i]);
	return (NULL);
}

/*
Returns true if the given character is a digit.
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
