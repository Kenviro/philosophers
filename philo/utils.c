/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:53:23 by kilian            #+#    #+#             */
/*   Updated: 2025/01/10 11:47:42 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	allocation(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
}

long long	get_time(void)
{
	struct timeval	time;
	long long		result;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result);
}

void	philo_utils(t_philo *philo, t_data *data)
{
	if (philo->data->nb_philo == 1)
	{
		usleep((philo->data->time_to_die * 1000) + 2000);
		pthread_mutex_unlock(&philo->forks);
	}
	if (philo->nb_meal == data->nb_must_eat && philo->has_eaten == 0)
	{
		philo->has_eaten = 1;
		data->nb_philo_eat++;
	}
}

static void	print_dead(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (philo->die == 1 && philo->data->dead == 1)
	{
		data->dead = 2;
		pthread_mutex_lock(&data->print);
		printf("%lld %d died\n", (get_time() - data->start), \
				philo->id);
		pthread_mutex_unlock(&data->print);
	}
	pthread_mutex_unlock(&data->dead_mutex);
}

void	*is_dead(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (data->dead == 0 && data->nb_philo_eat < data->nb_philo)
	{
		if ((get_time() - data->start) - philo->last_meal > data->time_to_die)
		{
			philo->die = 1;
			philo->data->dead = 1;
		}
		usleep(50);
	}
	if (philo->has_eaten == 0)
		print_dead(philo, data);
	return (NULL);
}
