/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/23 13:56:20 by ysetiawa         ###   ########.fr       */
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

void	add_back(t_node **stack, t_node *new_node)
{
	t_node	*temp;

	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	temp = *stack;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
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

t_node	*copy_list(t_node *src)
{
	t_node	*new_list;
	t_node	*current;
	t_node	*new_node;

	new_list = NULL;
	current = src;
	while (current)
	{
		new_node = create_node(current->data);
		if (!new_node)
			return (NULL);
		add_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

t_node	*find_last_node(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next != NULL)
		stack = stack->next;
	return (stack);
}
