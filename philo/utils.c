/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilian <kilian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:53:23 by kilian            #+#    #+#             */
/*   Updated: 2024/12/24 20:05:26 by kilian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	negative;
	int	result;

	result = 0;
	negative = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		negative *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
		{
			if (negative == -1)
				return (INT_MIN);
			return (INT_MAX);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * negative);
}

void	allocation(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->data.nb_philo);
	if (!table->philos)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	table->threads = malloc(sizeof(pthread_t) * table->data.nb_philo);
	if (!table->threads)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->data.nb_philo);
	if (!table->forks)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
}

void	free_all(t_table *table)
{
	free(table->philos);
	free(table->threads);
	free(table->forks);
}
