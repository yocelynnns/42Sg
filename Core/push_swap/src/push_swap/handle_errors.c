/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:30:21 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/05 14:40:03 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	error_syntax(char *arg)
{
	int	i;

	if (!(arg[0] == '+' || arg[0] == '-' || (arg[0] >= '0' && arg[0] <= '9')))
		return (1);
	if ((arg[0] == '+' || arg[0] == '-') && !(arg[1] >= '0' && arg[1] <= '9'))
		return (1);
	i = 1;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_dup(t_node *stack, int value)
{
	while (stack)
	{
		if (stack->data == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

void	free_stack(t_node **stack)
{
	t_node	*temp;
	t_node	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		temp = current->next;
		current->data = 0;
		free(current);
		current = temp;
	}
	*stack = NULL;
}

void	free_n_error(t_node **stack_a)
{
	free_stack(stack_a);
	write(1, "Error\n", 6);
	exit(1);
}
