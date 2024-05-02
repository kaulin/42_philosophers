/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:42:40 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/02 16:32:15 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_fed(t_data *data)
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	usage(void)
{
	printf("usage: ./philo number_of_philosophers time_to_die time_to_eat");
	printf(" /time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (2);
}

int	fail(t_data *data)
{
	printf("Error: %s\n", data->error);
	clean_data(data);
	return (KO);
}
