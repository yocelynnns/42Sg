/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:14:22 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/12 18:46:15 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	handle_sorting(t_node **stack_a, t_node **stack_b)
{
	if (stack_size(*stack_a) == 2)
		sa(stack_a);
	else if (stack_size(*stack_a) == 3)
		sort_three(stack_a);
	else if (stack_size(*stack_a) <= 5)
		sort_five(stack_a, stack_b);
	else
		sort_stacks(stack_a, stack_b);
}

char	**assign_arr(char **argv, int argc)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * argc);
	i = 0;
	while (argv[i])
	{
		arr[i] = ft_strdup(argv[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	setup_stack(int argc, char **argv, t_node **stack_a, int *is_split)
{
	int		i;

	*is_split = 0;
	if (argc == 1 || (argc == 2 && !(argv)[1][0]))
		return (1);
	if (argc == 2)
	{
		argv = ft_split((argv)[1], ' ');
		*is_split = 1;
	}
	else
	{
		argv++;
		argv = assign_arr(argv, argc);
	}
	init_stack_a(stack_a, argv);
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return (0);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		is_split;

	stack_a = NULL;
	stack_b = NULL;
	if (setup_stack(argc, argv, &stack_a, &is_split))
		return (1);
	if (!check_sorted(stack_a))
		handle_sorting(&stack_a, &stack_b);
	free_stack(&stack_a);
	return (0);
}
