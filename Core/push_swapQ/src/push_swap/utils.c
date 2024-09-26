/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:36 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/25 20:38:02 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	find_min(t_node *stack)
{
	int		index;
	int		min_index;
	long	smallest;
	t_node	*current;

	index = 0;
	min_index = 0;
	smallest = LONG_MAX;
	current = stack;
	while (current)
	{
		if (current->data < smallest)
		{
			smallest = current->data;
			min_index = index;
		}
		index++;
		current = current->next;
	}
	return (min_index);
}

t_node	*find_max(t_node *stack)
{
	long	biggest;
	t_node	*max_index;

	if (!stack)
		return (NULL);
	biggest = LONG_MIN;
	while (stack)
	{
		if (stack->data > biggest)
		{
			biggest = stack->data;
			max_index = stack;
		}
		stack = stack->next;
	}
	return (max_index);
}

t_median	find_median(t_node *sorted_list)
{
	int			node_count;
	t_node		*current;
	t_median	median;
	int			mid_position;
	int			i;

	node_count = stack_size(sorted_list);
	current = sorted_list;
	if (node_count == 0)
	{
		median.value = 0;
		median.index = 0;
		return (median);
	}
	mid_position = node_count / 5;
	i = 0;
	while (i < mid_position)
	{
		current = current->next;
		i++;
	}
	median.value = current->data;
	median.index = mid_position;
	return (median);
}
