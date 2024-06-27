/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:42:40 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/27 09:30:19 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
