/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:13:31 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/23 20:09:02 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*sort_list(t_node *stack_a)
{
	int		swap;
	t_node	*i;
	t_node	*j;
	t_node	*end;

	end = NULL;
	if (!stack_a)
		return (NULL);
	while (end != stack_a->next)
	{
		i = stack_a;
		while (i->next != end)
		{
			j = i->next;
			if (i->data > j->data)
			{
				swap = i->data;
				i->data = j->data;
				j->data = swap;
			}
			i = i->next;
		}
		end = i;
	}
	return (stack_a);
}

void	sort_stacks(t_node **stack_a, t_node **stack_b)
{
	process_nodes_with_new_median(stack_a, stack_b);
	find_and_push_biggest_with_cost_analysis(stack_a, stack_b);
}
