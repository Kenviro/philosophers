/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:38 by kilian            #+#    #+#             */
/*   Updated: 2025/01/08 16:15:27 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo, long long start)
{
	pthread_mutex_lock(&philo->table->data.print);
	printf("%lld philo %d is sleeping\n", (get_time() - start), philo->id);
	pthread_mutex_unlock(&philo->table->data.print);
	usleep(philo->table->data.time_to_sleep * 1000);
}

static void	think(t_philo *philo, long long start)
{
	pthread_mutex_lock(&philo->table->data.print);
	printf("%lld philo %d is thinking\n", (get_time() - start), philo->id);
	pthread_mutex_unlock(&philo->table->data.print);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks);
	pthread_mutex_lock(philo->next_fork);
}

static void	eat(t_philo *philo, long long start)
{
	philo->last_meal = (get_time() - start);
	pthread_mutex_lock(&philo->table->data.print);
	printf("%d philo %d is eating\n", philo->last_meal, philo->id);
	pthread_mutex_unlock(&philo->table->data.print);
	usleep(philo->table->data.time_to_eat * 1000);
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(philo->next_fork);
}

void	*philo_routine(void *arg)
{
	t_philo				*philo;
	t_data				data;

	philo = (struct s_philo *)arg;
	data = philo->table->data;
	while (1)
	{
		think(philo, data.start);
		take_forks(philo);
		eat(philo, data.start);
		philo->nb_meal++;
		philo_sleep(philo, data.start);
		if (philo->nb_meal == data.nb_must_eat)
			return (NULL);
	}
}
