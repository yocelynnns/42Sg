/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:53:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/19 21:32:17 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void process_nodes_with_new_median(t_node **stack_a, t_node **stack_b)
{
    t_node *temp_stack;
    t_median median;

    while (stack_size(*stack_a) > 1)
    {
        if (stack_size(*stack_a) <= 5)
        {
            sort_five(stack_a, stack_b);
            break;
        }
        temp_stack = copy_list(*stack_a);
        if (!temp_stack)
        {
            printf("Memory allocation failed\n");
            return;
        }
        temp_stack = sort_list(temp_stack);
        median = find_median(temp_stack);
        process_nodes(stack_a, stack_b, median.value);
        if (temp_stack)
            free_stack(&temp_stack);
    }
}

void process_nodes(t_node **stack_a, t_node **stack_b, int median_value)
{
    int total_nodes;
    int nodes_processed;
    t_node *current;
    t_node *temp;
    int has_smaller;
    t_node *last_node;

    total_nodes = stack_size(*stack_a);
    nodes_processed = 0;
    while (nodes_processed < total_nodes)
    {
        current = *stack_a;
        if (current->data < median_value)
            pb(stack_a, stack_b);
        else
        {
            temp = *stack_a;
            has_smaller = 0;
            last_node = find_last_node(*stack_a);
            while (temp)
            {
                if (temp->data < median_value)
                {
                    has_smaller = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!has_smaller)
                break;
            if (last_node->data < median_value)
                rra(stack_a); 
            else
                ra(stack_a);
        }
        nodes_processed++;
    }
}

void find_and_push_biggest(t_node **stack_a, t_node **stack_b)
{
    t_node *biggest;
    t_node *current;
    t_node *last_node;
    int is_biggest;

    while (*stack_b)
    {
        if (!*stack_b)
            return;
        biggest = find_max(*stack_b);
        current = *stack_b;
        last_node = find_last_node(*stack_a);
        is_biggest = 0;
        while (current->next)
        {
            current = current->next;
            if (current->data > biggest->data)
            {
                biggest = current;
                is_biggest = 0;
            }
        }
        if (!is_biggest)
        {
            while (biggest != *stack_b)
            {
                if (last_node->data == biggest->data)
                    rrb(stack_b); 
                else
                    rb(stack_b);
            }
        }
        pa(stack_a, stack_b);
    }
}
