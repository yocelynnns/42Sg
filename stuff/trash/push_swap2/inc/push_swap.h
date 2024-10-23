/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:28:16 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/22 19:08:13 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_node
{
    int data;
    struct s_node *next;
    struct s_node *prev;
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




#endif
