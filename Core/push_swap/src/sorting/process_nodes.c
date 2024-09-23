/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:53:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/23 20:18:54 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void process_nodes_with_new_median(t_node **stack_a, t_node **stack_b)
{
    t_median median;

    while (stack_size(*stack_a) > 1)
    {
        if (stack_size(*stack_a) <= 5)
        {
            sort_five(stack_a, stack_b);
            break;
        }
        
        median = find_median(*stack_a); // Use a quick median finding approach here
        process_nodes(stack_a, stack_b, median.value);
    }
}

int	has_smaller_node(t_node *stack, int median_value)
{
	while (stack)
	{
		if (stack->data < median_value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

void process_nodes(t_node **stack_a, t_node **stack_b, int median_value)
{
    t_node *current;
    int total_nodes = stack_size(*stack_a);
    int nodes_processed = 0;

    while (nodes_processed < total_nodes)
    {
        current = *stack_a;
        
        if (current->data < median_value)
        {
            pb(stack_a, stack_b);
            nodes_processed++;  // Increment only on successful push
        }
        else
        {
            // Check if any smaller nodes are left
            if (!has_smaller_node(*stack_a, median_value))
                break;  // Stop if no smaller nodes

            // Use a simpler rotation logic
            if (find_last_node(*stack_a)->data < median_value)
                rra(stack_a);
            else
                ra(stack_a);
        }
    }
}


void	rotate_to_biggest(t_node **stack_b, t_node *biggest)
{
	while (biggest != *stack_b)
	{
		if (find_last_node(*stack_b)->data == biggest->data)
			rrb(stack_b);
		else
			rb(stack_b);
	}
}

int calculate_rotation_cost(t_node *stack, t_node *target)
{
    int forward_cost = 0;
    int reverse_cost = 0;
    t_node *temp = stack;

    // Calculate forward rotation cost
    while (temp && temp != target)
    {
        forward_cost++;
        temp = temp->next;
    }

    // Calculate reverse rotation cost
    temp = stack;
    while (temp && temp != target)
    {
        reverse_cost++;
        temp = temp->prev;
    }

    // Return the minimum cost
    return (forward_cost < reverse_cost) ? forward_cost : reverse_cost;
}

void find_and_push_biggest_with_cost_analysis(t_node **stack_a, t_node **stack_b)
{
    while (*stack_b)
    {
        t_node *biggest = find_max(*stack_b);
        int cost = calculate_rotation_cost(*stack_b, biggest);
        
        if (cost < stack_size(*stack_b) / 2)
        {
            while (biggest != *stack_b)
                rb(stack_b);  // Forward rotate
        }
        else
        {
            while (biggest != *stack_b)
                rrb(stack_b);  // Reverse rotate
        }
        
        pa(stack_a, stack_b);
    }
}


