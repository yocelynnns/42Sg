/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:12:00 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/11/19 19:05:38 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_threads(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&philo[i].thread_id, NULL, \
		philo_routine, &philo[i]) != 0)
			return (printf("Error: Failed to create philosopher thread\n"), -1);
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL, monitoring, table) != 0)
		return (printf("Error: Failed to create monitoring thread\n"), -1);
	pthread_join(table->monitor_thread, NULL);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	return (0);
}

int	init_mtx(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	if (!table->forks)
		return (printf("Error: Memory allocation failed\n"), -1);
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (printf("Error: Failed to initialize fork mutex\n"), -1);
		i++;
	}
	if (pthread_mutex_init(&table->print_mtx, NULL) != 0)
		return (printf("Error: Failed to initialize print mutex\n"), -1);
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
		return (printf("Error: Failed to initialize state mutex\n"), -1);
	return (0);
}

int	init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo[i].id = i + 1;
		philo[i].meals_count = 0;
		philo[i].last_meal = table->start_time;
		philo[i].table = table;
		philo[i].first_fork = &table->forks[i];
		philo[i].next_fork = &table->forks[(i + 1) % table->philo_nbr];
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL) != 0)
			return (printf("Error: Failed to initialize meal mutex"), -1);
		i++;
	}
	philo->table = table;
	return (0);
}

void	init_all(t_philo **philo, t_table *table, char **argv)
{
	table->philo_nbr = ft_atoi(argv[1]);
	table->die_time = ft_atol(argv[2]);
	table->eat_time = ft_atol(argv[3]);
	table->sleep_time = ft_atol(argv[4]);
	table->alive = 1;
	if (argv[5])
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	if (init_mtx(table) != 0)
		return ;
	*philo = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!*philo)
	{
		printf("Error: Memory allocation failed\n");
		return ;
	}
	init_philo(*philo, table);
	table->philo = *philo;
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->philo->meal_mutex);
	pthread_mutex_destroy(&table->state_mutex);
	free(table->forks);
}

// void	destroy_mutexes(t_table *table)
// {
// 	int	i;
// 	int	forks;
// 	int	print_mtx;
// 	int	meal_mtx;

// 	i = 0;
// 	while (i < table->philo_nbr)
// 	{
// 		forks = pthread_mutex_destroy(&table->forks[i]);
// 		i++;
// 	}
// 	print_mtx = pthread_mutex_destroy(&table->print_mtx);
// 	meal_mtx = pthread_mutex_destroy(&table->philo->meal_mutex);
// 	if (forks == 0 && print_mtx == 0 && meal_mtx == 0)
// 		printf("Mutex destroyed successfully.\n");
// 	else if (forks == EBUSY || print_mtx == EBUSY || meal_mtx == EBUSY)
// 		printf("Failed to destroy mutex: Mutex is busy.\n");
// 	else if (forks == EINVAL || print_mtx == EINVAL || meal_mtx == EINVAL)
// 		printf("Failed to destroy mutex: Invalid mutex.\n");
// 	free(table->forks);
// }
