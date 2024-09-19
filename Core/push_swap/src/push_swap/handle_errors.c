/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:30:21 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/19 21:32:54 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Simple argument validation function
int error_syntax(char *arg)
{
	int i;

    if (!(arg[0] == '+' || arg[0] == '-' || (arg[0] >= '0' && arg[0] <= '9')))
        return (1); // Check if the first character isn't a sign or a digit

    if ((arg[0] == '+' || arg[0] == '-') && !(arg[1] >= '0' && arg[1] <= '9'))
        return (1); // Check if the first character is a sign, but the second character isn't a digit

    i = 1;
    while (arg[i])
    {
        if (arg[i] < '0' || arg[i] > '9')
            return (1); // Check if any subsequent character isn't a digit
        i++;
    }
    return (0);
}

// Function to check for duplicate values
int	check_dup(t_node *stack, int value) 
{
	while (stack) 
	{
		if (stack->data == value) 
			return (1); //Check if the current node value = value u want to add
		stack = stack->next; 
    }
	return (0);
}

void	free_stack(t_node **stack)
{
	t_node	*temp;
	t_node	*curr;

	if (!stack)
		return ;
	curr = *stack;
	while (curr)
	{
		temp = curr->next;
		curr->data = 0;
		free(curr);
		curr = temp;
	}
	*stack = NULL;
}

// Error handling function
void	free_n_error(t_node **stack_a) //error msg & freestack
{
	free_stack(stack_a);
	printf("Error\n");
	exit(1);
}
