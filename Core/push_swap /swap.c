/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:22:42 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/01 17:18:08 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_node **stack_a)
{
	t_node	*first;
	t_node	*second;

	first = *stack_a;
	second = first->next;
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	first->next = second->next;
	second->next = first;
	*stack_a = second;
}

void	sb(t_node **stack_b)
{
	t_node	*first;
	t_node	*second;

	first = *stack_b;
	second = first->next;
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	first->next = second->next;
	second->next = first;
	*stack_b = second;
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	sa(stack_a);
	sb(stack_b);
}
