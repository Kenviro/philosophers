/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:53:23 by kilian            #+#    #+#             */
/*   Updated: 2025/01/08 16:13:44 by ktintim-         ###   ########.fr       */
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
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		pthread_mutex_destroy(&table->philos->forks);
		i++;
	}
	pthread_mutex_destroy(&table->data.print);
	free(table->philos);
	free(table->threads);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		result;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result);
}
