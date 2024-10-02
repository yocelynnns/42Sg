/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:05:18 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/02 17:01:24 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	process_nodes_with_fixed_ranges(t_node **stack_a, \
t_node **stack_b, int total_elements)
{
	int	range_size;
	int	i;
	int	lower_bound;
	int	upper_bound;
	int	current_median;

	if (stack_size(*stack_a) <= 100)
		range_size = total_elements / 3;
	else
		range_size = total_elements / 5;
	i = 0;
	while (i < 5)
	{
		lower_bound = i * range_size + 1;
		if (i == 4)
			upper_bound = total_elements;
		else
			upper_bound = (i + 1) * range_size;
		current_median = (lower_bound + upper_bound) / 2;
		push_range_to_stack_b(stack_a, stack_b, lower_bound, \
		upper_bound, current_median);
		i++;
	}
}

void	push_range_to_stack_b(t_node **stack_a, \
t_node **stack_b, int lower_bound, int upper_bound, int median_b)
{
	int		pushed_count;
	int		total_pushed;
	t_node	*current;

	pushed_count = 0;
	total_pushed = 0;
	current = *stack_a;
	while (current)
	{
		if (current->data >= lower_bound && current->data <= upper_bound)
			total_pushed++;
		current = current->next;
	}
	while (*stack_a && pushed_count < total_pushed)
	{
		current = *stack_a;
		if (stack_size(*stack_a) <= 5)
			break ;
		if (current->data >= lower_bound && current->data <= upper_bound)
		{
			pb(stack_a, stack_b);
			pushed_count++;
			if ((*stack_b)->data < median_b)
				rb(stack_b);
		}
		else
			ra(stack_a);
	}
}

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
