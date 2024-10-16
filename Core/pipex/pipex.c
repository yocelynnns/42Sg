/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:35:33 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/15 21:24:10 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//open -> 0 is infile which is RD_ONLY
//open -> 1 is outfile which is WR, CREA, TRUN

//0 means stdin read
//1 means stdout write
//2 means stderr error

void    childp(char **argv, int *pipe_fd, char **env)
{
    int infile;

    infile = open(argv[1], O_RDONLY);
    if (infile == -1)
    {
		perror("Error Infile");
        exit(1);
    }
    dup2(infile, STDIN_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(infile);
    execute(argv[2], env);
}

void    parentp(char **argv, int *pipe_fd, char **env)
{
    int outfile;

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1)
    {
		perror("Error Outfile");
        exit(1);
    }
    dup2(pipe_fd[0], STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(pipe_fd[1]);
    close(outfile);
    execute(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
    int pipe_fd[2];
    pid_t   pid;
    
	if (argc != 5)
    {
        ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
        exit(1);
    }
    if (pipe(pipe_fd) == -1)
        return (perror("Error pipe"), 1);
    pid = fork();
    if (pid == -1)
        return (perror("Error Fork"), 1);
    if (pid == 0)
        childp(argv, pipe_fd, env);
    else
    {
        parentp(argv, pipe_fd, env);
        waitpid(pid, NULL, 0);
    }
}
