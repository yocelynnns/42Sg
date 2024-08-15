/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:28:16 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/15 19:19:13 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int data;
    struct s_node *next;
} t_node;

// Push Swap operations
void sa(t_node **stack_a);
void sb(t_node **stack_b);
void ss(t_node **stack_a, t_node **stack_b);
void pa(t_node **stack_a, t_node **stack_b);
void pb(t_node **stack_a, t_node **stack_b);
void ra(t_node **stack_a);
void rb(t_node **stack_b);
void rr(t_node **stack_a, t_node **stack_b);
void rra(t_node **stack_a);
void rrb(t_node **stack_b);
void rrr(t_node **stack_a, t_node **stack_b);

// Utility functions
t_node *createNode(int data);
void push(t_node **top, int newData);
int pop(t_node **top);
void printList(t_node *node);

#endif
