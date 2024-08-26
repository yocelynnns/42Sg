/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:36:08 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/07/30 14:43:05 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_b;

	top_b = *stack_b;
	if (*stack_b == NULL)
		return ;
	*stack_b = top_b->next;
	top_b->next = *stack_a;
	*stack_a = top_b;
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_a;

	top_a = *stack_a;
	if (*stack_a == NULL)
		return ;
	*stack_a = top_a->next;
	top_a->next = *stack_b;
	*stack_b = top_a;
}
