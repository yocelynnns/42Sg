/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:36 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/23 16:22:52 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static long	ft_atol(const char *str)
{
	long res;
    int sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || \ 
            *str == '\v' || *str == '\r')
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

t_node	*find_smallest(t_node *stack) 
{
	long			smallest; //smallest value
	t_node	*smallest_n; //pointer to smallest number

	if (!stack)
		return (NULL);
	smallest = LONG_MAX;
	while (stack)
	{
		if (stack->data < smallest) 
		{
			smallest = stack->data; 
			smallest_n = stack; 
		}
		stack = stack->next;
	}
	return (smallest_n); 
}

t_node	*find_largest(t_node *stack) 
{
	long			largest; //largest value
	t_node	*largest_n; //pointer to largest number

	if (!stack)
		return (NULL);
	largest = LONG_MIN; 
	while (stack) 
	{
		if (stack->data > largest) 
		{
			largest = stack->data; 
			largest_n = stack; 
		}
		stack = stack->next;
	}
	return (largest_n);
}