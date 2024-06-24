/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:44:15 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/30 13:39:30 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*tempnode;

	head = *lst;
	while (head)
	{
		tempnode = head->next;
		(*del)(head->content);
		free(head);
		head = tempnode;
	}
	*lst = NULL;
}
