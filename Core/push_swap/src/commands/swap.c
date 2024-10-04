/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:22:42 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/02 15:20:59 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_node **stack_a)
{
	t_node	*first;
	t_node	*second;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	first = *stack_a;
	second = (*stack_a)->next;
	*stack_a = second;
	first->next = second->next;
	second->next = first;
	write(1, "sa\n", 3);
}

void	sb(t_node **stack_b)
{
	t_node	*first;
	t_node	*second;

	if (*stack_b && (*stack_b)->next)
	{
		first = *stack_b;
		second = first->next;
		if (*stack_b == NULL || (*stack_b)->next == NULL)
			return ;
		first->next = second->next;
		second->next = first;
		*stack_b = second;
		write(1, "sb\n", 3);
	}
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	sa(stack_a);
	sb(stack_b);
}
