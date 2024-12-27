/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilian <kilian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:58 by kilian            #+#    #+#             */
/*   Updated: 2024/12/24 20:18:21 by kilian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->data.nb_philo)
	{
		table->philos[i].id = i;
		table->philos[i].last_meal = 0;
		table->philos[i].nb_meal = 0;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_table		table;
	int			i;

	i = 0;
	parse_args(argc, argv, &table.data);
	allocation(&table);
	init(&table);
	while (i < table.data.nb_philo)
	{
		pthread_create(&table.threads[i], NULL, &philo_routine, &table);
		i++;
	}
	// join_threads(&table);
	free_all(&table);
}
