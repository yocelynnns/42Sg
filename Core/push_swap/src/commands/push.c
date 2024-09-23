/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:36:08 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/23 13:52:21 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*first_b;

	if (!stack_b || !*stack_b)
		return ;
	if (!stack_a || !*stack_a)
		return ;
	first_b = *stack_b;
	*stack_b = (*stack_b)->next;
	first_b->next = *stack_a;
	*stack_a = first_b;
	printf("pa\n");
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
	printf("pb\n");
}
