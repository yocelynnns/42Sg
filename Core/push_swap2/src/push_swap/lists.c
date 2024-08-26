/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/22 20:14:23 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_node(int value)
{ 
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->data = value;
	new_node->next = NULL;
	return (new_node);
}

void	add_back(t_node **node, t_node *new)
{
	t_node	*temp;

	if (*node == NULL)
	{
		*node = new;
		return ;
	}
	temp = *node;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	stack_size(t_node *stack) 
{
	int	count;

	if (!stack) 
		return (0);
	count = 0;
	while (stack) 
	{
		stack = stack->next; 
		count++;
	}
	return (count);
}

