/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:39:07 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/11/18 00:36:55 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	long			last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	meal_mutex;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				philo_nbr;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			start_time;
	int				max_meals;
	int				alive;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	state_mutex;
	pthread_t		monitor_thread;
	t_philo			*philo;
}	t_table;

int			ft_isdigit(int c);
int			ft_isdigit_str(const char *str);
int			ft_atoi(const char *nptr);
int			ft_strcmp(char *s1, char *s2);
int			check_valid(int argc, char **argv);
int			ft_strlen(const char *s);
long		ft_atol(const char *str);
int			philo_threads(t_philo *philo, t_table *table);
int			init_mtx(t_table *table);
int			init_philo(t_philo *philo, t_table *table);
void		init_all(t_philo **philo, t_table *table, char **argv);
void		destroy_mutexes(t_table *table);
int			check_philosopher_death(t_table *table, int i);
int			check_all_done(t_table *table);
void		*monitoring(void *arg);
void		one_philo(t_philo *philo);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
void		*philo_routine(void *arg);
void		print_action(t_philo *philo, const char *action);
long		timestamp(void);
long long	get_elapsed_time(long long start_time);

#endif