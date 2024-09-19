/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:14:22 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/19 21:32:50 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	init_stack_a(&stack_a, argv + 1);
	if (!check_sorted(stack_a)) 
	{
		if (stack_size(stack_a) == 2) //If not, and there are two numbers, swap the first two nodes
			sa(&stack_a);
		else if (stack_size(stack_a) == 3) //If not, and there are three numbers, call the sort three algorithm
			sort_three(&stack_a);
		else if (stack_size(stack_a) == 4 || stack_size(stack_a) == 5)
			sort_five(&stack_a, &stack_b);
		else
			sort_stacks(&stack_a, &stack_b); //If not, and there are more than three numbers, call the sort stacks algorithm
	}
	free_stack(&stack_a); 
	return (0);
}
