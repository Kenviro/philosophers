/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:30:58 by kilian            #+#    #+#             */
/*   Updated: 2025/01/08 16:33:02 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
}

static void	init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = 0;
		table->philos[i].nb_meal = 0;
		pthread_mutex_init(&table->philos[i].forks, NULL);
		table->philos[i].table = table;
		i++;
	}
	i = 0;
	while (i < table->data.nb_philo)
	{
		if (i == table->data.nb_philo - 1)
			table->philos[i].next_fork = &table->philos[0].forks;
		else
			table->philos[i].next_fork = &table->philos[i + 1].forks;
		i++;
	}
	table->data.start = get_time();
}

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;

	i = 0;
	parse_args(argc, argv, &table);
	allocation(&table);
	init(&table);
	i = 0;
	while (i < table.data.nb_philo)
	{
		if (pthread_create(&table.threads[i], NULL, \
			&philo_routine, &table.philos[i]) != 0)
		{
			perror("Erreur création thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	join_threads(&table);
	free_all(&table);
}
