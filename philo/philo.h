/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:32:11 by kilian            #+#    #+#             */
/*   Updated: 2025/01/22 18:41:46 by ktintim-         ###   ########.fr       */
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

typedef struct s_data
{
	int				error;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	long long		start;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	pthread_t		monitoring;
	struct s_global	*global;
	struct s_philo	*philos;
}				t_data;

typedef struct s_global
{
	int				dead;
	int				nb_philo_eat;
	pthread_mutex_t	g_lock;
}				t_global;

typedef struct s_philo
{
	int				finish;
	int				id;
	long long		last_meal;
	int				nb_meal;
	int				fork;
	int				next_fork;
	int				eated;
	pthread_mutex_t	forks;
	pthread_mutex_t	*next_forks;
	pthread_t		is_dead;
	pthread_t		thread;
	t_data			data;
	t_global		*global;
}				t_philo;

// philosophers.c
void		value_error(t_data *data);

// parse.c
t_global	*init_global(t_data *data);
int			main_utils(t_data *data);
void		parse_args(int argc, char **argv, t_data *data);
void		has_eaten(t_data *data, int i);
int			create_thread(t_data *data);

// arg_check.c
int			ft_atoi(char *str);
int			check_letter(char **argv);
void		free_all(t_data *data);
void		check_error(t_data *data, int argc, char **argv);

// routine.c
void		*philo_routine(void *arg);

// utils.c
void		allocation(t_data *data);
void		*is_dead(void *arg);
long long	get_time(void);

// print.c
void		release_forks(t_philo *philo);
void		print(char *str, t_philo *philo, long long start);
void		print_1_philo(t_data *data);
void		get_all_time(t_data *data);
void		ft_usleep(long long time);

#endif