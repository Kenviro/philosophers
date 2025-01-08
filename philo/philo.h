/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:32:11 by kilian            #+#    #+#             */
/*   Updated: 2025/01/08 16:33:47 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_data {
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	long long		start;
	pthread_mutex_t	print;
}				t_data;

typedef struct s_philo {
	int				id;
	int				last_meal;
	int				nb_meal;
	pthread_mutex_t	forks;
	pthread_mutex_t	*next_fork;
	struct s_table	*table;
}				t_philo;

typedef struct s_table {
	t_data			data;
	t_philo			*philos;
	pthread_t		*threads;
}				t_table;

// parse.c
void		parse_args(int argc, char **argv, t_table *table);

// routine.c
void		*philo_routine(void *arg);

// utils.c
int			ft_atoi(char *str);
void		allocation(t_table *table);
void		free_all(t_table *table);
long long	get_time(void);

#endif