/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:58 by kilian            #+#    #+#             */
/*   Updated: 2025/01/10 11:51:40 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static void	init_philo(t_data *data, int i)
{
	data->philos[i].die = 0;
	data->philos[i].id = i + 1;
	data->philos[i].last_meal = 0;
	data->philos[i].nb_meal = 0;
	data->philos[i].has_eaten = 0;
	pthread_mutex_init(&data->philos[i].forks, NULL);
	data->philos[i].data = data;
}

static void	init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		init_philo(data, i);
		i++;
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		if (data->nb_philo == 1)
			data->philos[i].next_fork = NULL;
		else if (i == data->nb_philo - 1)
			data->philos[i].next_fork = &data->philos[0].forks;
		else
			data->philos[i].next_fork = &data->philos[i + 1].forks;
	}
	data->start = get_time();
	pthread_mutex_init(&data->dead_mutex, NULL);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philos[i].forks);
		i++;
	}
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->print);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	i = 0;
	parse_args(argc, argv, &data);
	allocation(&data);
	init(&data);
	i = 0;
	while (i < data.nb_philo)
	{
		if (pthread_create(&data.philos[i].thread, NULL, \
			&philo_routine, &(data.philos[i])) != 0)
		{
			perror("Erreur création thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	join_threads(&data);
	free_all(&data);
	return (0);
}
