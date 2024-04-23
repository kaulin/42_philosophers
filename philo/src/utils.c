/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:42:40 by jajuntti          #+#    #+#             */
/*   Updated: 2024/04/23 14:45:12 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("DATA\n");
	printf("dead_flag: %d\n", data->dead_flag);
	printf("seats: %d\n", data->seats);
	printf("meal_target: %d\n", data->dead_flag);
	printf("die_time: %d\n", data->die_time);
	printf("eat_time: %d\n", data->eat_time);
	printf("sleep_time: %d\n", data->sleep_time);
	printf("error: %s\n", data->error);
	printf("\nFORKS\n");
	while (i < data->seats)
	{
		printf("Fork %d @ %x\n", i, (int)&data->forks[i]);
		i++;
	}
	i = 0;
	printf("\nPHILOS\n");
	while (i < data->seats)
	{
		printf("philo %d [%x] id: %d\n", i, (int)&data->philos[i], data->philos[i].id);
		printf("print_lock: %x\n", (int)&data->philos[i].print_lock);
		i++;
	}
	printf("\n");
}

void	print_philo(t_philo *philo)
{
	printf("PHILO ");
	printf("id: %d @ %x\n", philo->id, (int)philo);
	printf("start_time: %zu\n", philo->start_time);
	printf("lfork: %x\n", (int)philo->lfork);
	printf("rfork: %x\n", (int)philo->rfork);
	printf("meal_count: %d\n", philo->meal_count);
	printf("eating_flag: %d\n", philo->eating_flag);
	printf("dead_flag: %d\n", philo->dead_flag);
	printf("print_lock: %x\n", (int)philo->print_lock);
	printf("\n");
}