/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilian <kilian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:38 by kilian            #+#    #+#             */
/*   Updated: 2024/12/24 19:35:07 by kilian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	t_data 	data;
	int		time_start;

	table = (struct t_table *)arg;
	philo = table->philos;
	data = table->data;
	gettimefday(&time_start, NULL);
	while (1)
	{
		// take_forks(philo);
		// eat(philo);
		// sleep(philo);
		// think(philo);
		if (philo->nb_meal == data.nb_must_eat)
			return (NULL);
	}
}
