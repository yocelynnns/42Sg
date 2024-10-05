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

void	handle_syntax_error(char **argv, int i, t_node **stack_a)
{
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	free_n_error(stack_a);
}

void	check_value_errors(long value, t_node **stack_a)
{
	if (value > INT_MAX || value < INT_MIN)
		free_n_error(stack_a);
}

void	process_node(t_node **stack_a, char *arg)
{
	t_node	*new_node;
	long	value;

	value = ft_atol(arg);
	check_value_errors(value, stack_a);
	if (check_dup(*stack_a, (int)value))
		free_n_error(stack_a);
	new_node = create_node((int)value);
	if (!new_node)
		free_n_error(stack_a);
	add_back(stack_a, new_node);
}

void	init_stack_a(t_node **stack_a, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			handle_syntax_error(argv, i, stack_a);
		process_node(stack_a, argv[i]);
		i++;
	}
}
