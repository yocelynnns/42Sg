/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_groups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:25:44 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/24 20:31:00 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort_group1(t_node **stack_a, t_node **stack_b) {
    int pushed_count = 0;
    int total_pushed = 0;

    t_node *current = *stack_a;
    while (current) {
        if (current->data >= 21 && current->data <= 40) {
            total_pushed++;
        }
        current = current->next;
    }
    while (*stack_a && pushed_count < total_pushed)
    {
        t_node *current = *stack_a;
        t_node *last_node = find_last_node(*stack_a);
        t_node *second_last_node = find_second_last_node(*stack_a);

        if (current->data >= 21 && current->data <= 40)
        {
            pb(stack_a, stack_b);
            pushed_count++;
        }
        if (last_node->data >= 21 && last_node->data <= 40)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 21 && second_last_node->data <= 40)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else
        {
            ra(stack_a);
        }
    }
}

void sort_group2(t_node **stack_a, t_node **stack_b) {
    int pushed_count = 0;
    int total_pushed = 0;

    t_node *current = *stack_a;
    while (current)
    {
        if ((current->data >= 1 && current->data <= 20) \
        || (current->data >= 41 && current->data <= 60)) {
            total_pushed++;
        }
        current = current->next;
    }
    while (*stack_a && pushed_count < total_pushed) {
        t_node *current = *stack_a;
        t_node *last_node = find_last_node(*stack_a);
        t_node *second_last_node = find_second_last_node(*stack_a);

        if (current->data >= 1 && current->data <= 20)
        {
            pb(stack_a, stack_b);
            rb(stack_b);
            pushed_count++;
        }
        if (last_node->data >= 1 && last_node->data <= 20)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 1 && second_last_node->data <= 20)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (current->data >= 41 && current->data <= 60)
        {
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (last_node->data >= 41 && last_node->data <= 60)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 41 && second_last_node->data <= 60)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else {
            ra(stack_a);
        }
    }
}

void sort_group3(t_node **stack_a, t_node **stack_b) {
    int pushed_count = 0;
    int total_pushed = 0;

    t_node *current = *stack_a;
    while (current) {
        if (current->data >= 61 && current->data <= 80) {
            total_pushed++;
        }
        current = current->next;
    }
    while (*stack_a && pushed_count < total_pushed) {
        t_node *current = *stack_a;
        t_node *last_node = find_last_node(*stack_a);
        t_node *second_last_node = find_second_last_node(*stack_a);

        if (current->data >= 61 && current->data <= 80) {
            pb(stack_a, stack_b);
            pushed_count++;
        }
        if (last_node->data >= 61 && last_node->data <= 80)
        {
            rra(stack_a); // Rotate current node to the end
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else if (second_last_node->data >= 61 && second_last_node->data <= 80)
        {
            rra(stack_a); // Rotate twice to move the second last node to the top
            rra(stack_a);
            pb(stack_a, stack_b);
            pushed_count++;
        }
        else {
            ra(stack_a);
        }
    }
}

