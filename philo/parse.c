/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:51:56 by kilian            #+#    #+#             */
/*   Updated: 2025/01/10 11:15:20 by ktintim-         ###   ########.fr       */
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

static int	ft_atoi(char *str)
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
	pthread_mutex_init(&data->print, NULL);
	data->dead = 0;
	data->nb_philo_eat = 0;
}
