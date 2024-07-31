/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:35 by ysetiawa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/29 21:44:08 by ysetiawa         ###   ########.fr       */
=======
/*   Updated: 2024/07/30 18:56:05 by ysetiawa         ###   ########.fr       */
>>>>>>> 2fb7992 (push)
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

<<<<<<< HEAD
void	ft_lstadd_front(t_node **lst, t_node *new)
{
	new->next = *lst;
	*lst = new;
}

t_node	*ft_lstnew(int *data)
{
	t_node	*newnode;

	newnode = (t_node *)malloc(sizeof(t_node));
	if (!newnode)
		return (NULL);
	newnode->data = data;
	newnode->next = NULL;
	return (newnode);
}

=======
t_node	*createNode(int *data)
{
	t_node	*newNode;

	newNode = (t_node *)malloc(sizeof(t_node));
	if (!newNode)
		return (NULL);
	newNode->data = data;
	newNode->next = NULL;
	return (newNode);
}

void	push(t_node **top, t_node *newData)
{
	t_node *newNode;
	
	newNode = createNode(newData);
	newNode->next = *top;
	*top = newNode;
}

int pop(t_node **top)
{
	t_node	*temp;
	int		popped;

	temp = *top;
	popped = temp->data;
    if (*top == NULL)
        return ;
    *top = (*top)->next;
    
    free(temp);
    return popped;
}
>>>>>>> 2fb7992 (push)
