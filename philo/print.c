/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:27:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/01/23 14:34:50 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(philo->next_forks);
	}
	else
	{
		pthread_mutex_unlock(philo->next_forks);
		pthread_mutex_unlock(&philo->forks);
	}
}

void	print(char *str, t_philo *philo, long long start)
{
	pthread_mutex_lock(&philo->global->g_lock);
	if (philo->finish == 0)
	{
		// pthread_mutex_unlock(&philo->global->g_lock);
		// pthread_mutex_lock(&philo->data.print);
		printf("%lld %d %s\n", (get_time() - start), philo->id, str);
		// pthread_mutex_unlock(&philo->data.print);
		// pthread_mutex_lock(&philo->global->g_lock);
	}
	pthread_mutex_unlock(&philo->global->g_lock);
}

void	print_1_philo(t_data *data)
{
	printf("0 1 is thinking\n");
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%d 1 died\n", data->time_to_die);
}

void	get_all_time(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_philo)
	{
		data->philos[i].data.start = data->start;
		i++;
	}
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}
