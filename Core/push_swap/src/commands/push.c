/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:36:08 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/12 18:45:49 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*first_b;

	if (!stack_b || !*stack_b)
		return ;
	first_b = *stack_b;
	*stack_b = (*stack_b)->next;
	first_b->next = *stack_a;
	*stack_a = first_b;
	write(1, "pa\n", 3);
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_a;

	if (*stack_a == NULL)
		return ;
	top_a = *stack_a;
	*stack_a = top_a->next;
	if (*stack_a)
		(*stack_a)->prev = NULL;
	top_a->next = *stack_b;
	if (*stack_b)
		(*stack_b)->prev = top_a;
	*stack_b = top_a;
	write(1, "pb\n", 3);
}
