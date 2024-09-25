/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:39:20 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/22 16:23:16 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_node **stack_a)
{
	t_node	*prev;
	t_node	*curr;

	prev = NULL;
	curr = *stack_a;
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	while (curr->next != NULL)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev != NULL)
	{
		prev->next = NULL;
		curr->next = *stack_a;
		*stack_a = curr;
		printf("rra\n");
	}
}

void	rrb(t_node **stack_b)
{
	t_node	*prev;
	t_node	*curr;

	prev = NULL;
	curr = *stack_b;
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	while (curr->next != NULL)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev != NULL)
	{
		prev->next = NULL;
		curr->next = *stack_b;
		*stack_b = curr;
	}
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}
