/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:26:41 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/07/30 16:36:18 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_node **stack_a)
{
	t_node	*first;
	t_node	*last;

	first = *stack_a;
	last = first;
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	while (last->next != NULL)
		last = last->next;
	*stack_a = first->next;
	first->next = NULL;
	last->next = first;
}

void	rb(t_node **stack_b)
{
	t_node	*first;
	t_node	*last;

	first = *stack_b;
	last = first;
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	while (last->next != NULL)
		last = last->next;
	*stack_b = first->next;
	first->next = NULL;
	last->next = first;
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	ra(stack_a);
	rb(stack_b);
}
