/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:39:20 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/05 14:39:49 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_node **stack_a)
{
	t_node	*last;
	t_node	*second_last;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	last = *stack_a;
	while (last->next->next)
		last = last->next;
	second_last = last;
	last = last->next;
	second_last->next = NULL;
	last->next = *stack_a;
	*stack_a = last;
	write(1, "rra\n", 4);
}

void	rrb(t_node **stack_b)
{
	t_node	*last;
	t_node	*second_last;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	last = *stack_b;
	while (last->next->next)
		last = last->next;
	second_last = last;
	last = last->next;
	second_last->next = NULL;
	last->next = *stack_b;
	*stack_b = last;
	write(1, "rrb\n", 4);
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}
