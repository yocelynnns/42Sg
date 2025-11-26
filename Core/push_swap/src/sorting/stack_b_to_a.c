/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_b_to_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:21:44 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/12 18:46:30 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_pushable_nodes(t_node *stack, t_node *max_node)
{
	int	index_push;

	index_push = 0;
	while (stack)
	{
		if (stack != max_node)
		{
			stack = stack->next;
			index_push++;
		}
		else
			break ;
	}
	return (index_push);
}

void	handle_max_conditions(t_node **stack_a, \
t_node **stack_b, t_node *max_node)
{
	int	index;
	int	median;
	int	temp;

	index = count_pushable_nodes(*stack_b, max_node);
	median = stack_size(*stack_b) / 2;
	if (index < median)
	{
		while (index)
		{
			rb(stack_b);
			index--;
		}
		pa(stack_a, stack_b);
	}
	else
	{
		temp = stack_size(*stack_b) - index;
		while (temp)
		{
			rrb(stack_b);
			temp--;
		}
		pa(stack_a, stack_b);
	}
}

void	find_and_push_biggest(t_node **stack_a, t_node **stack_b)
{
	t_node	*max_node;

	while (*stack_b)
	{
		max_node = find_max(*stack_b);
		handle_max_conditions(stack_a, stack_b, max_node);
	}
}
