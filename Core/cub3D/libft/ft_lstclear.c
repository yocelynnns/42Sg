/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:20:26 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/19 21:20:26 by yocelynnns       ###   ########.fr       */
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
