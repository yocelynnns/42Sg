/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:54:12 by messs             #+#    #+#             */
/*   Updated: 2025/02/26 17:01:39 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <limits.h>

long	ft_atol(char *str, t_minishell *mini)
{
	unsigned long long	result;
	int					sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (check_limit(sign, result, mini, str))
			break ;
		i++;
	}
	return (result * sign);
}

int	check_is_number(char *str)
{
	int	i;

	if (str == NULL || *str == '\0')
		return (0);
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (str[i] == '\0');
}

int	ft_exit(char **av, t_minishell *mini)
{
	int	i;

	i = 0;
	if (av[1] && check_is_number(av[1]) == 0)
	{
		ft_putstr_fd("exit\n", STDERR);
		print_exit_error(av[1]);
		cleanup(mini);
		exit(2);
	}
	if (av[1] && av[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		mini->exit = 1;
		return (1);
	}
	if (av[1])
		mini->exit = ft_atol(av[1], mini);
	if (mini->exit_flag == 0)
		ft_putstr_fd("exit\n", STDERR);
	i = mini->exit;
	cleanup(mini);
	exit(i % 256);
}

int	add_env_node(char *new_value, t_env **env, t_minishell *mini)
{
	t_env	*new_node;
	t_env	*last;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (print_export_error(-1, ft_strdup(new_value), mini));
	new_node->value = new_value;
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
	{
		last = *env;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	return (SUCCESS);
}
