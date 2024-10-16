/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:28:49 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/15 21:40:15 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		perror("Error path");
		exit(1);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("Error exec");
		free(path);
	}
	while (cmd[++i])
        free(cmd[i]);
    free(cmd);
    exit(1);
}

char	*find_path(char *cmd, char **envp)
{
	char	**all_path;
	char	*path;
	int		i;
	char	*add_backs;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	all_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_path[i])
	{
		add_backs = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(add_backs, cmd);
		free(add_backs);
		if (access(path, F_OK) == 0)
		{
            int j = 0;
            while (all_path[j])
                free(all_path[j++]);
            free(all_path);
            return (path);
        }
		free(path);
		i++;
	}
	i = -1;
	while (all_path[++i])
		free(all_path[i]);
	free(all_path);
	return (0);
}
