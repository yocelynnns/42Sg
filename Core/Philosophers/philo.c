/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:38:38 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/11/19 16:17:54 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_valid(int argc, char **argv)
{
	int	i;
	int	len;
	int	value;

	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i]) == 0)
			return (printf("Error: Not a valid input!\n"), -1);
		len = ft_strlen(argv[i]);
		if (len > 10 || (len == 10 && ft_strcmp(argv[i], "2147483647") > 0))
			return (printf("Error: Exceeds int max value!\n"), -1);
		value = ft_atoi(argv[i]);
		if (i == 1 && (value < 1))
			return (printf("Error: There must be at least 1 philo\n"), -1);
		if ((i >= 2 && i <= 4) && value <= 0)
			return (printf("Error: Time should not be 0 or negative\n"), -1);
		if (i == 5 && value <= 0)
			return (printf("Error: Meal should not be 0 or negative\n"), -1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		if (!check_valid(argc, argv))
		{
			table.start_time = timestamp();
			init_all(&philo, &table, argv);
			if (philo != NULL)
				philo_threads(philo, &table);
			destroy_mutexes(&table);
			free(philo);
		}
	}
	else
		return (printf("Error!\nUsage: ./philo 5 800 200 200 [5]\n"), 1);
	return (0);
}
