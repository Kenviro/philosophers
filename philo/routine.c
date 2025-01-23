/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:38 by kilian            #+#    #+#             */
/*   Updated: 2025/01/23 14:20:27 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	long long	time_to_think;

	print("is thinking", philo, philo->data.start);
	if (philo->id % 2 == 0)
		return ;
	time_to_think = philo->data.time_to_eat / 2 - philo->data.time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 1;
	if (philo->data.nb_philo % 2 == 1)
		ft_usleep((time_to_think) * 0.2);
}

static void	take_forks(t_philo *philo)
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

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->g_lock);
	philo->last_meal = get_time();
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->global->g_lock);
	print("is eating", philo, philo->data.start);
	ft_usleep(philo->data.time_to_eat);
	release_forks(philo);
}

static void	p_sleep(t_philo *philo)
{
	print("is sleeping", philo, philo->data.start);
	ft_usleep(philo->data.time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		usleep(200);
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
