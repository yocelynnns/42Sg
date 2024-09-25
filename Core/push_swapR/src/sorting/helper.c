/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:38:58 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:20 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// t_node *find_last_node(t_node *stack)
// {
//     if (!stack)
//         return NULL;
//     while (stack->next != NULL)
//         stack = stack->next;
//     return stack;
// }

t_node *find_second_last_node(t_node *stack)
{
    if (!stack || !stack->next)
        return NULL;
    while (stack->next->next != NULL)
        stack = stack->next;
    return stack;
}