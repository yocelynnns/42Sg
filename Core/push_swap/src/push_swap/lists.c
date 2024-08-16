/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/16 19:12:59 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*createNode(int data)
{ 
	t_node	*newNode;

	newNode = (t_node *)malloc(sizeof(t_node));
	if (!newNode)
		return (NULL);
	newNode->data = data;
	newNode->next = NULL;
	return (newNode);
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

void	push(t_node **top, int newData)
{
	t_node *newNode;
	
	newNode = createNode(newData);
	if (!newNode)
        return;
	newNode->next = *top;
	*top = newNode;
}

int		pop(t_node **top)
{
	t_node	*temp;
	int		popped;

	temp = *top;
	popped = temp->data;
    if (*top == NULL)
        return (0);
    *top = (*top)->next;
    free(temp);
    return (popped);
}

void printList(t_node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int	stack_sz(t_node *stack) 
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

