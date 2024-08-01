/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/01 17:07:03 by ysetiawa         ###   ########.fr       */
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

void	push(t_node **top, int newData)
{
	t_node *newNode;
	
	newNode = createNode(newData);
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