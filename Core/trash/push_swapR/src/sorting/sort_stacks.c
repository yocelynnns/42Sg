/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:13:31 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/24 20:36:03 by ysetiawa         ###   ########.fr       */
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
	sort_group1(stack_a, stack_b);
    sort_group2(stack_a, stack_b);
    sort_group3(stack_a, stack_b);
    process_nodes_with_new_median(stack_a, stack_b);
    find_and_push_biggest(stack_a, stack_b);
}
