/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:42:40 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/02 16:40:50 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Checks the hungry_ones array of integers to see if all the philosophers have 
been fed enough times already. If a hungry philosopher is encountered, returns 
KO (1), else returns OK (1).
*/
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

/*
Prints a usage message specifying the required arguments.
*/
int	usage(void)
{
	printf("usage: ./philo number_of_philosophers time_to_die time_to_eat");
	printf(" /time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (2);
}

/*
Prints "Error: " followed by the message stored in data->error. Then cleans 
the data struct and returns KO (1).
*/
int	fail(t_data *data)
{
	printf("Error: %s\n", data->error);
	clean_data(data);
	return (KO);
}
