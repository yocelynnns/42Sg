/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:28:16 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/05 20:33:46 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				data;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_median
{
	int	value;
	int	index;
}	t_median;

typedef struct s_push_range_params
{
	int	lower_bound;
	int	upper_bound;
	int	median_b;
	int	pushed_count;
	int	total_pushed;
}	t_push_range_params;

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
int			ft_isdigit(int c);
int			wordlen(const char *s, char c);
char		*writeword(char const *s, int len);
char		**free_array(char **ptr, int i);
char		**split_words(const char *s, char c, int word_count);
char		**ft_split(char const *s, char c);
int			error_syntax(char *arg);
int			check_dup(t_node *stack, int value);
void		free_stack(t_node **stack);
void		free_n_error(t_node **stack_a);
t_node		*create_node(int value);
void		add_back(t_node **stack, t_node *new_node);
int			stack_size(t_node *stack);
t_node		*copy_list(t_node *src);
t_node		*find_last_node(t_node *stack);
void		free_argv(char **argv);
void		handle_sorting(t_node **stack_a, t_node **stack_b);
int			setup_stack(int argc, char **argv, t_node **stack_a, \
int *is_split);
int			main(int argc, char **argv);
void		handle_syntax_error(char **argv, int i, t_node **stack_a);
void		check_value_errors(long value, t_node **stack_a, char **argv);
void		process_node(t_node **stack_a, long value, char **argv);
void		init_stack_a(t_node **stack_a, char **argv);
long		ft_atol(const char *str);
int			find_min(t_node *stack);
t_node		*find_max(t_node *stack);
t_median	find_median(t_node *sorted_list);
t_node		*sort_list(t_node *stack_a);
void		assign_indices(t_node *stack_a, t_node *sorted_list);
void		sort_stacks(t_node **stack_a, t_node **stack_b);
int			check_sorted(t_node *stack);
void		sort_three(t_node **stack_a);
void		sort_five(t_node **stack_a, t_node **stack_b);
void		push_range_to_stack_b(t_node **stack_a, t_node **stack_b, \
t_push_range_params *params);
int			count_nodes_in_range(t_node *stack_a, int lower_bound, \
int upper_bound);
bool		push_to_stack_b_if_in_range(t_node **stack_a, t_node **stack_b, \
	t_node *current, t_push_range_params *params);
void		process_nodes_with_fixed_ranges(t_node **stack_a, \
t_node	**stack_b, int total_elements);
int			count_pushable_nodes(t_node *stack, t_node *max_node);
void		handle_max_conditions(t_node **stack_a, \
t_node **stack_b, t_node *max_node);
void		find_and_push_biggest(t_node **stack_a, t_node **stack_b);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		**assign_arr(char **argv, int argc);

#endif