/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:27:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/01/15 16:36:25 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, t_philo *philo, long long start)
{
	pthread_mutex_lock(&philo->data.print);
	printf("%lld %d %s\n", (get_time() - start), philo->id, str);
	pthread_mutex_unlock(&philo->data.print);
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
