/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:21:25 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 01:29:06 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

int ft_list_size(t_list *begin_list)
{
    t_list *lst;
    int count = 0;

    lst = begin_list;

    while(lst != NULL)
    {
        lst = lst->next;
        count++;
    }
    return (count);
}