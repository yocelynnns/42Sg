/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:58:02 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/11/19 17:10:33 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_table *table, int i)
{
	int		died;
	long	time_since_last_meal;

	died = 0;
	pthread_mutex_lock(&table->philo[i].meal_mutex);
	time_since_last_meal = timestamp() - table->philo[i].last_meal;
	pthread_mutex_unlock(&table->philo[i].meal_mutex);
	if (time_since_last_meal > table->die_time)
	{
		pthread_mutex_lock(&table->state_mutex);
		table->alive = 0;
		pthread_mutex_unlock(&table->state_mutex);
		if (table->philo_nbr != 1)
			printf("%ld %d died\n", timestamp() \
			- table->start_time, table->philo[i].id);
		died = 1;
	}
	return (died);
}

int	check_all_done(t_table *table)
{
	int	all_done;
	int	i;

	all_done = 1;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		if (table->max_meals == -1 || table->philo[i].meals_count \
		< table->max_meals)
			all_done = 0;
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
		if (!all_done)
			break ;
		i++;
	}
	return (all_done);
}

void	*monitoring(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1 && table->philo_nbr != 1)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (check_philosopher_death(table, i))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&table->state_mutex);
		if (check_all_done(table) && table->max_meals != -1)
		{
			table->alive = 0;
			pthread_mutex_unlock(&table->state_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&table->state_mutex);
		usleep(5000);
	}
	return (NULL);
}
