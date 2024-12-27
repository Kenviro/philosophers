/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilian <kilian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:51:56 by kilian            #+#    #+#             */
/*   Updated: 2024/12/24 19:57:11 by kilian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	else
		data->nb_must_eat = -1;
	if (check_arg(data, argc))
	{
		printf("Error: wrong argument\n");
		exit(1);
	}
}
