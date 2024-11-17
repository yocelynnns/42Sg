/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:11:49 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/11/18 00:36:39 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	usleep(philo->table->die_time * 1000 + 1000);
	print_action(philo, "died");
	pthread_mutex_unlock(philo->first_fork);
	return ;
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->next_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->first_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->first_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->next_fork);
		print_action(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = timestamp();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	usleep(philo->table->eat_time * 1000);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->next_fork);
}

void	sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->table->sleep_time * 1000);
	print_action(philo, "is thinking");
	usleep(2000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->philo_nbr == 1)
		one_philo(philo);
	else
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		while (1)
		{
			pthread_mutex_lock(&philo->table->state_mutex);
			if (!philo->table->alive || (philo->table->max_meals \
			!= -1 && philo->meals_count >= philo->table->max_meals))
			{
				pthread_mutex_unlock(&philo->table->state_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->table->state_mutex);
			take_forks(philo);
			eat(philo);
			sleep_and_think(philo);
		}
	}
	return (NULL);
}
