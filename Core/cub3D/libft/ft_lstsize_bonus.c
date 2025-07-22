/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:30:41 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/30 13:39:45 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		count;

	node = lst;
	count = 0;
	while (node != NULL)
	{
		node = node->next;
		count++;
	}
	return (count);
}
