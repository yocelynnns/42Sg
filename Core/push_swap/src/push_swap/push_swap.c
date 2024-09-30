/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:14:22 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/25 21:23:14 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_list(t_node *stack)
{
	t_node	*current;

	current = stack;
	if (!stack)
	{
		printf("List is empty\n");
		return ;
	}
	while (current)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void print_list_with_label(t_node *stack, const char *label)
{
    if (!stack)
    {
        printf("%s: List is empty\n", label);
        return;
    }

    printf("%s: ", label);
    t_node *current = stack;
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    t_node *stack_a;
    t_node *stack_b;

	stack_a = NULL;
	stack_b = NULL;
    if (argc == 1 || (argc == 2 && !argv[1][0]))
        return (1);
    else if (argc == 2)
        argv = ft_split(argv[1], ' ');
    else
        argv++;
    init_stack_a(&stack_a, argv);
    if (!check_sorted(stack_a))
	{
        if (stack_size(stack_a) == 2)
                sa(&stack_a);
        else if (stack_size(stack_a) == 3)
            sort_three(&stack_a);
        else if (stack_size(stack_a) <= 5)
            sort_five(&stack_a, &stack_b);
        else
            sort_stacks(&stack_a, &stack_b);
	}
    free_stack(&stack_a);
    return (0);
}

