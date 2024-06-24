/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:12:06 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/30 13:39:40 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*temp;

	head = NULL;
	while (lst)
	{
		temp = (*f)(lst->content);
		new = ft_lstnew(temp);
		if (!new)
		{
			ft_lstclear(&head, *del);
			del(temp);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		lst = lst -> next;
	}
	return (head);
}
