/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:12:55 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/25 21:16:07 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_sorted(t_node *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->data > stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	sort_three(t_node **stack_a)
{
	t_node	*biggest;

	biggest = find_max(*stack_a);
	if (*stack_a == biggest)
		ra(stack_a);
	else if ((*stack_a)->next == biggest)
		rra(stack_a);
	if ((*stack_a)->data > (*stack_a)->next->data)
		sa(stack_a);
}

void	sort_five(t_node **stack_a, t_node **stack_b)
{
	int	smallest;

	while (stack_size(*stack_a) > 3)
	{
		smallest = find_min(*stack_a);
		if (smallest == 0)
			pb(stack_a, stack_b);
		else if (smallest <= stack_size(*stack_a) / 2)
			ra(stack_a);
		else
			rra(stack_a);
	}
	sort_three(stack_a);
	pa(stack_a, stack_b);
	pa(stack_a, stack_b);
	if ((*stack_a)->data > (*stack_a)->next->data)
		sa(stack_a);
}
