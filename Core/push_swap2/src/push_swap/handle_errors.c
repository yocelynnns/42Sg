/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:30:21 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/22 20:27:33 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

int	error_argvs(char *argvs) 
{
	if (!(*argvs == '+' || *argvs == '-' || (*argvs >= '0' && *argvs <= '9'))) 
		return (1); //Check if the 1st char isnt a sign or a digit
	if ((*argvs == '+' || *argvs == '-') && !(argvs[1] >= '0' && argvs[1] <= '9')) 
		return (1); //Check if the 1st char is a sign, but 2nd char isnt a digit
	while (*++argvs) //If no error, increment till the end
	{
		if (!(*argvs >= '0' && *argvs <= '9')) 
			return (1); //Check if the next char isnt a digit
	}
	return (0);
}

int	check_dup(t_node *stack_a, int value) 
{
	t_node *temp;
    
	while (stack_a) 
	{
		if (stack_a->data == value) 
			return (1); //Check if the current node value = value u want to add
		stack_a = stack_a->next; 
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

void	free_n_error(t_node **stack_a) //error msg & freestack
{
	free_stack(stack_a);
	ft_printf("Error\n");
	exit(1);
}