/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:32:11 by kilian            #+#    #+#             */
/*   Updated: 2025/01/10 11:47:14 by ktintim-         ###   ########.fr       */
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
	int				nb_philo_eat;
	int				dead;
	long long		start;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	struct s_philo	*philos;
}				t_data;

typedef struct s_philo {
	int				die;
	int				id;
	int				last_meal;
	int				nb_meal;
	int				has_eaten;
	pthread_mutex_t	forks;
	pthread_mutex_t	*next_fork;
	pthread_t		is_dead;
	pthread_t		thread;
	t_data			*data;
}				t_philo;

// philosophers.c
void		free_all(t_data *data);

// parse.c
void		parse_args(int argc, char **argv, t_data *data);

// routine.c
void		*philo_routine(void *arg);

// utils.c
void		philo_utils(t_philo *philo, t_data *data);
void		allocation(t_data *data);
void		*is_dead(void *arg);
long long	get_time(void);

#endif