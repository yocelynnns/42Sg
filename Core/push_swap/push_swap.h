/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:28:16 by ysetiawa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/29 21:45:50 by ysetiawa         ###   ########.fr       */
=======
/*   Updated: 2024/07/30 16:51:34 by ysetiawa         ###   ########.fr       */
>>>>>>> 2fb7992 (push)
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// # include "../libft/libft.h"
// # include "../ft_printf/ft_printf.h"

# include <stdlib.h>

typedef struct s_node
{
<<<<<<< HEAD
    int data;
    struct s_node *next;
} t_node;

t_node *ft_lstnew(int *data);
// void ft_lstadd_front(t_node **lst, t_node *new);
void sa(t_node **stack_a);
void sb(t_node **stack_b);
void ss(t_node **stack_a, t_node **stack_b);
=======
	int				data;
	struct s_node	*next;
}	t_node;

void	pa(t_node **stack_a, t_node **stack_b);
void	pb(t_node **stack_a, t_node **stack_b);
void	rra(t_node **stack_a);
void	rrb(t_node **stack_b);
void	rrr(t_node **stack_a, t_node **stack_b);
void	ra(t_node **stack_a);
void	rb(t_node **stack_b);
void	rr(t_node **stack_a, t_node **stack_b);
void	sa(t_node **stack_a);
void	sb(t_node **stack_b);
void	ss(t_node **stack_a, t_node **stack_b);
void	ft_lstadd_front(t_node **lst, t_node *new);
t_node	*ft_lstnew(int *data);
>>>>>>> 2fb7992 (push)

#endif