/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:53:23 by kilian            #+#    #+#             */
/*   Updated: 2025/01/23 14:33:10 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	allocation(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		printf("Error: malloc failed\n");
		data->error = 1;
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

static void	philo_finish(t_philo *philo, t_data data)
{
	int	i;

	i = 0;
	while (i < data.nb_philo)
	{
		pthread_mutex_lock(&philo->global->g_lock);
		philo[i].finish = 1;
		pthread_mutex_unlock(&philo->global->g_lock);
		i++;
	}
}

static void	print_dead(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->global->g_lock);
		if ((get_time() - data->philos[i].last_meal) > \
			data->time_to_die && data->global->dead == 0)
		{
			data->global->dead = 1;
			pthread_mutex_lock(&data->print);
			printf("%lld %d died\n", (get_time() - data->start), philo->id);
			pthread_mutex_unlock(&data->print);
		}
		pthread_mutex_unlock(&data->global->g_lock);
		has_eaten(data, i);
		i++;
		usleep(50);
	}
}

void	*is_dead(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->global->g_lock);
	while (data->global->nb_philo_eat < data->nb_philo && \
			data->global->dead == 0)
	{
		pthread_mutex_unlock(&data->global->g_lock);
		print_dead(data->philos, data);
		pthread_mutex_lock(&data->global->g_lock);
	}
	pthread_mutex_unlock(&data->global->g_lock);
	philo_finish(data->philos, *data);
	return (NULL);
}
