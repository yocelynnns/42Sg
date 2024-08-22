/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:55:45 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/16 17:31:47 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static long	ft_atol(const char *str)
{
	long res;
    int sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || \ 
            *str == '\v' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
        if (*str == '-')
		    sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}

int	check_sort(t_node *stack_a)
{
	if (!stack_a)
		return (1);
	while (stack_a->next)
	{
		if (stack_a->data > stack_a->next->data) 
			return (0); //Check if curr node value > next node
		stack_a = stack_a->next; 
	}
	return (1);
}
