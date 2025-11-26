/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:14:15 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/12 18:46:17 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	handle_syntax_error(char **argv, int i, t_node **stack_a)
{
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	free_n_error(stack_a);
}

void	check_value_errors(long value, t_node **stack_a, char **argv)
{
	int	i;

	if (value > INT_MAX || value < INT_MIN)
	{
		i = 0;
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
		free_n_error(stack_a);
	}
}

void	process_node(t_node **stack_a, long value, char **argv)
{
	t_node	*new_node;
	int		i;

	if (check_dup(*stack_a, (int)value))
	{
		i = 0;
		handle_syntax_error(argv, i, stack_a);
	}
	new_node = create_node((int)value);
	if (!new_node)
		free_n_error(stack_a);
	add_back(stack_a, new_node);
}

void	init_stack_a(t_node **stack_a, char **argv)
{
	int		i;
	long	value;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			handle_syntax_error(argv, i, stack_a);
		value = ft_atol(argv[i]);
		check_value_errors(value, stack_a, argv);
		process_node(stack_a, value, argv);
		i++;
	}
}
