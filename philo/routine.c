/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:38 by kilian            #+#    #+#             */
/*   Updated: 2025/01/15 16:50:18 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	if (philo->finish == 0)
		print("is thinking", philo, philo->data.start);
}

static void	take_forks(t_philo *philo)
{
	if (philo->finish == 0)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->forks);
			print("has taken a fork", philo, philo->data.start);
			pthread_mutex_lock(philo->next_forks);
			print("has taken a fork", philo, philo->data.start);
		}
		else
		{
			pthread_mutex_lock(philo->next_forks);
			print("has taken a fork", philo, philo->data.start);
			pthread_mutex_lock(&philo->forks);
			print("has taken a fork", philo, philo->data.start);
		}
	}
}

static void	eat(t_philo *philo)
{
	if (philo->finish == 0)
	{
		pthread_mutex_lock(&philo->global->g_lock);
		philo->last_meal = get_time();
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->global->g_lock);
		print("is eating", philo, philo->data.start);
		usleep(philo->data.time_to_eat * 1000);
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(philo->next_forks);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(philo->next_forks);
	}
}

static void	p_sleep(t_philo *philo)
{
	if (philo->finish == 0)
	{
		print("is sleeping", philo, philo->data.start);
		usleep(philo->data.time_to_sleep * 1000);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		usleep(100);
	if (philo->data.nb_philo == 1)
	{
		print("is thinking", philo, philo->data.start);
		print("has taken a fork", philo, philo->data.start);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->global->g_lock);
		if (philo->finish == 1)
			break ;
		pthread_mutex_unlock(&philo->global->g_lock);
		think(philo);
		take_forks(philo);
		eat(philo);
		p_sleep(philo);
	}
	pthread_mutex_unlock(&philo->global->g_lock);
	return (NULL);
}
