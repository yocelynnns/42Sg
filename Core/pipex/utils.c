/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:28:49 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/19 17:36:13 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	abs_path(char *argv, char **envp)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		perror("Failed to split command");
		exit(1);
	}
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
	else
		perror("No such file or directory");
	free_mem(cmd);
	exit(1);
}

void	split_and_exec(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		perror("Failed to split command");
		exit(1);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free_mem(cmd);
		perror("Command not found");
		exit(1);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("Error exec");
		free(path);
		free_mem(cmd);
		exit(1);
	}
	free(path);
	free_mem(cmd);
}

char	**get_all_paths(char **envp)
{
	char	**all_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
	{
		perror("Error: PATH not found");
		return (NULL);
	}
	all_path = ft_split(envp[i] + 5, ':');
	if (!all_path)
	{
		perror("Error splitting PATH");
		return (NULL);
	}
	return (all_path);
}

char	*check_command_path(char *cmd, char **all_path)
{
	char	*add_backs;
	char	*path;
	int		i;

	i = 0;
	while (all_path[i])
	{
		add_backs = ft_strjoin(all_path[i], "/");
		if (!add_backs)
		{
			perror("Error joining path");
			return (NULL);
		}
		path = ft_strjoin(add_backs, cmd);
		free(add_backs);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**all_path;
	char	*path;

	if (!envp || !cmd)
	{
		perror("Env or cmd missing");
		return (NULL);
	}
	all_path = get_all_paths(envp);
	if (!all_path)
		return (NULL);
	path = check_command_path(cmd, all_path);
	free_mem(all_path);
	return (path);
}
