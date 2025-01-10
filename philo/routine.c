/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:38 by kilian            #+#    #+#             */
/*   Updated: 2025/01/10 11:46:33 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo, long long start)
{
	if (philo->data->nb_philo > 1)
	{
		if (philo->data->dead == 0 && philo->data->nb_philo_eat \
				< philo->data->nb_philo)
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%lld %d is sleeping\n", (get_time() - start), philo->id);
			pthread_mutex_unlock(&philo->data->print);
		}
		if (philo->data->dead == 0)
			usleep(philo->data->time_to_sleep * 1000);
	}
}

static void	think(t_philo *philo, long long start)
{
	if (philo->data->dead == 0 && philo->data->nb_philo_eat \
			< philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d is thinking\n", (get_time() - start), philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
}

static void	take_forks(t_philo *philo, long long start)
{
	pthread_mutex_lock(&philo->forks);
	if (philo->data->dead == 0 && philo->data->nb_philo_eat \
			< philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d has taken a fork\n", (get_time() - start), philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	if (philo->next_fork != NULL)
		pthread_mutex_lock(philo->next_fork);
	if (philo->data->dead == 0 && philo->next_fork != NULL \
			&& philo->data->nb_philo_eat < philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d has taken a fork\n", (get_time() - start), philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
}

static void	eat(t_philo *philo, long long start)
{
	if (philo->data->nb_philo > 1)
	{
		philo->last_meal = (get_time() - start);
		if (philo->data->dead == 0 && philo->data->nb_philo_eat \
				< philo->data->nb_philo)
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%d %d is eating\n", philo->last_meal, philo->id);
			pthread_mutex_unlock(&philo->data->print);
		}
		if (philo->data->dead == 0 && philo->data->nb_philo_eat \
				< philo->data->nb_philo)
			usleep((philo->data->time_to_eat * 1000) + 2000);
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(philo->next_fork);
	}
}

void	*philo_routine(void *arg)
{
	t_philo				*philo;
	t_data				*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_create(&philo->is_dead, NULL, is_dead, philo);
	while (data->dead == 0 && data->nb_philo_eat < data->nb_philo)
	{
		think(philo, data->start);
		take_forks(philo, data->start);
		eat(philo, data->start);
		if (philo->data->nb_philo > 1)
			philo->nb_meal++;
		philo_sleep(philo, data->start);
		philo_utils(philo, data);
	}
	pthread_join(philo->is_dead, NULL);
	return (NULL);
}
