/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:53:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/26 20:51:41 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	process_nodes_with_new_median(t_node **stack_a, t_node **stack_b)
{
	t_node		*temp_stack;
	t_median	median;

    while (stack_size(*stack_a) > 1)
    {
        if (stack_size(*stack_a) <= 5)
        {
            sort_five(stack_a, stack_b);
            break;
        }
        temp_stack = copy_list(*stack_a);
		//print_list_with_label(temp_stack, "Temporary Sorted List");
        if (!temp_stack)
        {
            printf("Memory allocation failed\n");
            return;
        }
        temp_stack = sort_list(temp_stack);
        median = find_median(temp_stack);
		//printf("New Median value: %d\n", median.value);
        process_nodes(stack_a, stack_b, median.value);
		//print_list_with_label(*stack_a, "Stack A after processing new median");
       // print_list_with_label(*stack_b, "Stack B");
        if (temp_stack)
            free_stack(&temp_stack);
    }
}

void rotate_smaller_half(t_node **stack_b, int median_value_b)
{
    int total_rotated = 0;
    int total_nodes = stack_size(*stack_b);
    int rotated_count = 0;

    while (rotated_count < total_nodes)
    {
        if ((*stack_b)->data < median_value_b)
        {
            rb(stack_b); // Rotate smaller half of stack B
            total_rotated++;
        }
        rotated_count++;
    }
}

t_node *find_second_last_node(t_node *stack)
{
    if (!stack || !stack->next)
        return NULL;
    while (stack->next->next != NULL)
        stack = stack->next;
    return stack;
}

int count_pushable_nodes(t_node *stack, int median_value)
{
    int total_pushed = 0;
    while (stack)
    {
        if (stack->data < median_value)
            total_pushed++;
        stack = stack->next;
    }
    return total_pushed;
}

void another_split(t_node **stack_b, int median_v)
{
     if (!*stack_b || !(*stack_b)->next) return;
    t_node *current = *stack_b;

    //int new_median = (median_v / 2) + 1;

    // printf("New median for stack B: %d\n", median_v);
    // printf("Final Stack B: ");
    // print_list(*stack_b);

    current = *stack_b;
    int rotate_count = 0;
    int total_rotate = median_v;

    while (current && rotate_count < total_rotate)
    {
        if (current->data < median_v)
        {
            if (rotate_count < total_rotate) // Only rotate if we haven't pushed all required nodes
            {    
                rb(stack_b);
                rotate_count++;
                break;
            }
        }
        else
            break;
    }
}

void handle_push_conditions(t_node **stack_a, t_node **stack_b, int median_value, int *pushed_count)
{
   	t_node *current;
	t_node *last_node;
	t_node *second_last_node;

	current = *stack_a;
    last_node = find_last_node(*stack_a);
    second_last_node = find_second_last_node(*stack_a);
    int new_median = (median_value / 2); 
    if (stack_size(*stack_b) >= 2)
    {
        another_split(stack_b, new_median);
    }
    if (current->data < median_value || current->next->data < median_value)
    {
        if (current->next->data < median_value)
            sa(stack_a);
        pb(stack_a, stack_b);
        (*pushed_count)++;
        int new_median = (median_value / 2);  // Replace with correct median calculation if needed
            another_split(stack_b, new_median);
    }
    else if (last_node->data < median_value || second_last_node->data < median_value)
    {
        rra(stack_a);
        if (second_last_node->data < median_value)
            rra(stack_a);
        pb(stack_a, stack_b);
        (*pushed_count)++;
        int new_median = (median_value / 2);  // Replace with correct median calculation if needed
            another_split(stack_b, new_median);
    }
    else
        ra(stack_a);
}

void process_nodes(t_node **stack_a, t_node **stack_b, int median_value)
{
    int total_pushed;
    int pushed_count;

	total_pushed = count_pushable_nodes(*stack_a, median_value);
	pushed_count = 0;
    while (*stack_a && pushed_count < total_pushed)
    {
        if (!stack_a) break;
        handle_push_conditions(stack_a, stack_b, median_value, &pushed_count);
    }
}

void handle_max_conditions(t_node **stack_a, t_node **stack_b, t_node *max_node)
{
    t_node *current;
	t_node *last_node;
	t_node *second_last_node;

	current = *stack_b;
    last_node = find_last_node(*stack_b);
    second_last_node = find_second_last_node(*stack_b);
	if (current == max_node || current->next == max_node)
    {
        if (current->next == max_node)
            sb(stack_b);
        pa(stack_a, stack_b);
    }
    else if (last_node == max_node || second_last_node == max_node)
    {
        rrb(stack_b);
        if (second_last_node == max_node)
            rrb(stack_b);
        pa(stack_a, stack_b);
    }
    else
        rb(stack_b);
}

void find_and_push_biggest(t_node **stack_a, t_node **stack_b)
{
	t_node *max_node;
    t_node *temp_stack;
    t_median median_b;
    
    // After stack B contains 1-20, sort and find the new median
    temp_stack = copy_list(*stack_b); // Copy stack B to find the new median
    temp_stack = sort_list(temp_stack); // Sort stack B
    median_b = find_median(temp_stack); // Find the median of 1–20 in stack B

    // Rotate numbers smaller than the new median in stack B
    rotate_smaller_half(stack_b, median_b.value);

    // Now proceed with your original logic to push back the biggest numbers
    while (*stack_b)
    {
        max_node = find_max(*stack_b);
        handle_max_conditions(stack_a, stack_b, max_node);
    }

    if (temp_stack)
        free_stack(&temp_stack); // Free the temporary stack
}
