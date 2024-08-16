/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:53:04 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/16 17:03:58 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

t_node *ft_process(int argc, char **argv)
{
	t_node	*stack_a;
	int		i;
	int		j;

	i = 1;
	stack_a = NULL;
	if (argc < 2)
		print_error();
	if (argc == 2)
		stack_a = ft_sub_process(argv);
	else
	{
		while (i < argc)
		{
			j = ft_atol(argv[i]);
			add_back(&stack_a, createNode(j));
			i++;
		}
	}
	return (stack_a);
}

t_node	*next_process(char **argv)
{
	t_node	*stack_a;
	char	**temp;
	int		i;
	int		j;

	stack_a = NULL;
	i = 0;
	temp = ft_split(argv[1], 32);
	while (temp[i])
	{
		j = ft_atol(temp[i]);
		add_back(&stack_a, createNode(j));
		i++;
	}
	ft_freestr(temp);
	free(temp);
	return (stack_a);
}