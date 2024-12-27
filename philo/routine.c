/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilian <kilian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:38 by kilian            #+#    #+#             */
/*   Updated: 2024/12/27 15:54:28 by kilian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo)
{
	printf("%d philo %d is sleeping\n", get_time(), philo->id);
	usleep(philo->table->data.time_to_sleep * 1000);
}

static void	think(t_philo *philo)
{
	printf("%d philo %d is thinking\n", get_time(), philo->id);
	usleep(philo->table->data.time_to_sleep * 1000);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	pthread_mutex_lock(&philo->table->forks[(philo->id + 1) % philo->table->data.nb_philo]);
}

static void	eat(t_philo *philo)
{
	philo->last_meal = get_time();
	printf("%d philo %d is eating\n", philo->last_meal, philo->id);
	usleep(philo->table->data.time_to_eat * 1000);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
	pthread_mutex_unlock(&philo->table->forks[(philo->id + 1) % philo->table->data.nb_philo]);
}

void	*philo_routine(void *arg)
{
	t_table				*table;
	t_philo				*philo;
	t_data				data;

	table = (struct s_table *)arg;
	philo = table->philos;
	data = table->data;
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
		if (philo->nb_meal == data.nb_must_eat)
			return (NULL);
	}
}
