/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:14:22 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/26 21:14:29 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

int	main(int argc, char **argv) 
{
	t_node	*stack_a;
	t_node	*stack_b; 

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2) 
		argv = ft_split(argv[1], ' ');
	initial_a(&stack_a, argv + 1); //Initiate stack `a`, which also handles errors
	if (!check_sorted(stack_a)) 
	{
		if (stack_size(stack_a) == 2) //If not, and there are two numbers, swap the first two nodes
			sa(&stack_a);
		else if (stack_size(stack_a) == 3) //If not, and there are three numbers, call the sort three algorithm
			sort_three(&stack_a);
		else
			sort_stacks(&stack_a, &stack_b); //If not, and there are more than three numbers, call the sort stacks algorithm
	}
	free_stack(&stack_a); //Clean up the stack
	return (0);
}