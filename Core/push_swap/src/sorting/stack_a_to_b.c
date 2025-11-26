/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_a_to_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:05:18 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/12 18:46:28 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_range_to_stack_b(t_node **stack_a, t_node **stack_b, \
t_push_range_params *params)
{
	t_node	*current;

	while (*stack_a && params->pushed_count < params->total_pushed)
	{
		current = *stack_a;
		if (push_to_stack_b_if_in_range(stack_a, stack_b, current, params))
			continue ;
		ra(stack_a);
	}
}

int	count_nodes_in_range(t_node *stack_a, int lower_bound, int upper_bound)
{
	int		count;
	t_node	*current;

	count = 0;
	current = stack_a;
	while (current)
	{
		if (current->index >= lower_bound && current->index <= upper_bound)
			count++;
		current = current->next;
	}
	return (count);
}

bool	push_to_stack_b_if_in_range(t_node **stack_a, t_node **stack_b, \
	t_node *current, t_push_range_params *params)
{
	if (current->index >= params->lower_bound && current->index \
	<= params->upper_bound)
	{
		pb(stack_a, stack_b);
		params->pushed_count++;
		if ((*stack_b)->index < params->median_b)
			rb(stack_b);
		return (true);
	}
	return (false);
}

void	process_nodes_with_fixed_ranges(t_node **stack_a, \
t_node **stack_b, int total_elements)
{
	int					range_size;
	int					i;
	t_push_range_params	params;

	if (stack_size(*stack_a) <= 100)
		range_size = total_elements / 3;
	else
		range_size = total_elements / 5;
	i = 0;
	while (i < 5)
	{
		params.lower_bound = i * range_size + 1;
		if (i == 4)
			params.upper_bound = total_elements;
		else
			params.upper_bound = (i + 1) * range_size;
		params.median_b = (params.lower_bound + params.upper_bound) / 2;
		params.pushed_count = 0;
		params.total_pushed = count_nodes_in_range(*stack_a, \
		params.lower_bound, params.upper_bound);
		push_range_to_stack_b(stack_a, stack_b, &params);
		i++;
	}
}
