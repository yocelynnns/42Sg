/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:53:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/23 16:34:22 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	process_nodes_with_new_median(t_node **stack_a, t_node **stack_b)
{
	t_node		*temp_stack;
	t_median	median;

	while (stack_size(*stack_a) > 1)
	{
		if (stack_size(*stack_a) <= 5)
		{
			sort_five(stack_a, stack_b);
			break ;
		}
		temp_stack = copy_list(*stack_a);
		if (!temp_stack)
		{
			printf("Memory allocation failed\n");
			return ;
		}
		temp_stack = sort_list(temp_stack);
		median = find_median(temp_stack);
		process_nodes(stack_a, stack_b, median.value);
		if (temp_stack)
			free_stack(&temp_stack);
	}
}

int	has_smaller_node(t_node *stack, int median_value)
{
	while (stack)
	{
		if (stack->data < median_value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

void	process_nodes(t_node **stack_a, t_node **stack_b, int median_value)
{
	int		total_nodes;
	int		nodes_processed;
	t_node	*current;
	t_node	*last_node;

	total_nodes = stack_size(*stack_a);
	nodes_processed = 0;
	while (nodes_processed < total_nodes)
	{
		current = *stack_a;
		if (current->data < median_value)
			pb(stack_a, stack_b);
		else
		{
			last_node = find_last_node(*stack_a);
			if (!has_smaller_node(*stack_a, median_value))
				break ;
			if (last_node->data < median_value)
				rra(stack_a);
			else
				ra(stack_a);
		}
		nodes_processed++;
	}
}

void	rotate_to_biggest(t_node **stack_b, t_node *biggest)
{
	while (biggest != *stack_b)
	{
		if (find_last_node(*stack_b)->data == biggest->data)
			rrb(stack_b);
		else
			rb(stack_b);
	}
}

void	find_and_push_biggest(t_node **stack_a, t_node **stack_b)
{
	t_node	*biggest;
	t_node	*current;

	while (*stack_b)
	{
		biggest = find_max(*stack_b);
		current = *stack_b;
		while (current->next)
		{
			current = current->next;
			if (current->data > biggest->data)
				biggest = current;
		}
		rotate_to_biggest(stack_b, biggest);
		pa(stack_a, stack_b);
	}
}
