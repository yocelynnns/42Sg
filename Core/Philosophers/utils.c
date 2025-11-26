/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:32:04 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/11/19 18:13:09 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *action)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->table->print_mtx);
	pthread_mutex_lock(&philo->table->state_mutex);
	if (philo->table->alive)
	{
		timestamp = get_elapsed_time(philo->table->start_time);
		printf("%lld %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->table->state_mutex);
	pthread_mutex_unlock(&philo->table->print_mtx);
}

long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_elapsed_time(long long start_time)
{
	return (timestamp() - start_time);
}

long	ft_atol(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' \
			|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}
