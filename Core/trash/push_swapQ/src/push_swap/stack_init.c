/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:14:15 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/23 14:00:01 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack_a(t_node **stack_a, char **argv)
{
	t_node	*new_node;
	long	value;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			free_n_error(stack_a);
		value = ft_atol(argv[i]);
		if (value > INT_MAX || value < INT_MIN)
			free_n_error(stack_a);
		if (check_dup(*stack_a, (int)value))
			free_n_error(stack_a);
		new_node = create_node((int)value);
		if (!new_node)
			free_n_error(stack_a);
		add_back(stack_a, new_node);
		i++;
	}
}
