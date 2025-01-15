/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:51:56 by kilian            #+#    #+#             */
/*   Updated: 2025/01/15 16:11:07 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	get_all_time(data);
	pthread_create(&data->monitoring, NULL, &is_dead, data);
	while (i < data->nb_philo)
	{
		data->philos[i].data.start = get_time();
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
					&philo_routine, &(data->philos[i])) != 0)
		{
			perror("Erreur création thread");
			return (1);
		}
		i++;
	}
	return (0);
}

t_global	*init_global(t_data *data)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global)
	{
		printf("Error: malloc failed\n");
		data->error = 1;
	}
	global->dead = 0;
	global->nb_philo_eat = 0;
	pthread_mutex_init(&global->g_lock, NULL);
	return (global);
}

static int	check_arg(t_data *data, int argc)
{
	if (data->nb_philo < 1)
		return (1);
	if (data->time_to_die < 0)
		return (1);
	if (data->time_to_eat < 0)
		return (1);
	if (data->time_to_sleep < 0)
		return (1);
	if (data->nb_must_eat <= 0 && argc == 6)
		return (1);
	return (0);
}

void	parse_args(int argc, char **argv, t_data *data)
{
	data->error = 0;
	check_error(data, argc, argv);
	if (data->error == 0)
	{
		data->nb_philo = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
	}
	else
		value_error(data);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	else
		data->nb_must_eat = -1;
	if (check_arg(data, argc))
	{
		printf("Error: wrong argument\n");
		data->error = 1;
	}
}

void	has_eaten(t_data *data, int i)
{
	if (data->philos[i].nb_meal == data->nb_must_eat && \
				data->philos[i].eated == 0)
	{
		data->philos[i].eated = 1;
		data->global->nb_philo_eat++;
	}
}
