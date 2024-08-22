/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:53:04 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/22 20:43:55 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

void	sort_stacks(t_node **stack_a, t_node **stack_b) 
{
	int	size_a; 

	size_a = stack_size(*stack_a);
	while (size_a > 3 && !stack_sorted(*stack_a)) 
	{
		init_nodes_a(*stack_a, *stack_b); 
		move_a_to_b(stack_a, stack_b);
		size_a--;
	}
	sort_three(stack_a);
	while (*stack_b) 
	{
		init_nodes_b(*stack_a, *stack_b); 
		move_b_to_a(stack_a, stack_b); 
	}
	current_index(*stack_a); 
	min_on_top(stack_a);
}

