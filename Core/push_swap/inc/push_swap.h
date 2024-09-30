/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:28:16 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/26 21:26:34 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				data;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_median
{
	int	value;
	int	index;
}	t_median;

void		pa(t_node **stack_a, t_node **stack_b);
void		pb(t_node **stack_a, t_node **stack_b);
void		rra(t_node **stack_a);
void		rrb(t_node **stack_b);
void		rrr(t_node **stack_a, t_node **stack_b);
void		ra(t_node **stack_a);
void		rb(t_node **stack_b);
void		rr(t_node **stack_a, t_node **stack_b);
void		sa(t_node **stack_a);
void		sb(t_node **stack_b);
void		ss(t_node **stack_a, t_node **stack_b);
int			error_syntax(char *arg);
int			check_dup(t_node *stack, int value);
void		free_stack(t_node **stack);
void		free_n_error(t_node **stack_a);
t_node		*create_node(int value);
void		add_back(t_node **stack, t_node *new_node);
int			stack_size(t_node *stack);
t_node		*copy_list(t_node *src);
t_node		*find_last_node(t_node *stack);
void		init_stack_a(t_node **stack_a, char **argv);
long		ft_atol(const char *str);
int			find_min(t_node *stack);
t_node		*find_max(t_node *stack);
t_median	find_median(t_node *sorted_list);
int			wordlen(const char *s, char c);
char		*writeword(char const *s, int len);
char		**free_array(char **ptr, int i);
char		**split_words(const char *s, char c, int word_count);
char		**ft_split(char const *s, char c);
int			ft_isdigit(int c);
void		process_nodes_with_new_median(t_node **stack_a, t_node **stack_b);
void		process_nodes(t_node **stack_a, t_node **stack_b, int median_value);
void		find_and_push_biggest(t_node **stack_a, t_node **stack_b);
t_node		*sort_list(t_node *stack_a);
void		sort_stacks(t_node **stack_a, t_node **stack_b);
int			check_sorted(t_node *stack);
void		sort_three(t_node **stack_a);
void		sort_five(t_node **stack_a, t_node **stack_b);
void handle_max_conditions(t_node **stack_a, t_node **stack_b, t_node *max_node);
void process_nodes(t_node **stack_a, t_node **stack_b, int median_value);
void handle_push_conditions(t_node **stack_a, t_node **stack_b, int median_value, int *pushed_count);
int count_pushable_nodes(t_node *stack, int median_value);
t_node *find_second_last_node(t_node *stack);
void	print_list(t_node *stack);
void print_list_with_label(t_node *stack, const char *label);
void another_split(t_node **stack_b, int median_v);
void rotate_stack_b_based_on_median(t_node **stack_b, int median);
void process_nodes_with_fixed_ranges(t_node **stack_a, t_node **stack_b, int total_elements);
void push_range_to_stack_b(t_node **stack_a, t_node **stack_b, int lower_bound, int upper_bound, int median_b);

#endif