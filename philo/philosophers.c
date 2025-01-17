/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:58 by kilian            #+#    #+#             */
/*   Updated: 2025/01/17 10:45:00 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	value_error(t_data *data)
{
	data->nb_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->monitoring, NULL);
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static void	init_philo(t_data data, int i)
{
	data.philos[i].id = i + 1;
	data.philos[i].last_meal = get_time();
	data.philos[i].nb_meal = 0;
	data.philos[i].finish = 0;
	data.philos[i].fork = 0;
	data.philos[i].next_fork = 0;
	data.philos[i].eated = 0;
	pthread_mutex_init(&data.philos[i].forks, NULL);
	data.philos[i].data = data;
	data.philos[i].global = data.global;
}

static void	init(t_data data)
{
	int	i;

	i = 0;
	while (i < data.nb_philo)
	{
		init_philo(data, i);
		i++;
	}
	i = -1;
	while (++i < data.nb_philo)
	{
		if (data.nb_philo == 1)
			data.philos[i].next_forks = NULL;
		else if (i == data.nb_philo - 1)
			data.philos[i].next_forks = &data.philos[0].forks;
		else
			data.philos[i].next_forks = &data.philos[i + 1].forks;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;

	parse_args(argc, argv, &data);
	allocation(&data);
	data.global = init_global(&data);
	init(data);
	if (main_utils(&data) == 1)
		return (1);
	if (create_thread(&data) == 1)
		return (1);
	if (data.nb_philo != 1)
		join_threads(&data);
	free_all(&data);
	return (0);
}
