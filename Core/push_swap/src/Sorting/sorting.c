/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:19:37 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/22 20:13:36 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_sort(t_node *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->data > stack->next->data) 
			return (0); //Check if curr node value > next node
		stack = stack->next; 
	}
	return (1);
}

void	sort_three(t_node **stack_a) 
{
	t_node	*biggest; 

	biggest = find_max(*stack_a);
	if (biggest == *stack_a)
		ra(stack_a); //If the 1st node is the biggest rotate to bottom
	else if ((*stack_a)->next == biggest) 
		rra(stack_a); //If the 2nd node is the biggest rerotate bottom to top
	if ((*stack_a)->data > (*stack_a)->next->data) 
		sa(stack_a); //If the bottom node is the biggest, but the top node is higher than the second node, swap 
}
