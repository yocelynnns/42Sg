/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:35:33 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/19 19:17:01 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_mem(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	execute(char *argv, char **envp)
{
	if (argv[0] == '/')
		abs_path(argv, envp);
	else
		split_and_exec(argv, envp);
}

void	childp(char **argv, int *pipe_fd, char **env)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror("Error Infile");
		exit(1);
	}
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(infile);
	execute(argv[2], env);
}

void	parentp(char **argv, int *pipe_fd, char **env)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
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
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	status = 1;
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
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
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

// void	execute(char *argv, char **envp)
// {
// 	if (argv[0] == '/')
// 		abs_path(argv, envp);
// 	else
// 		split_and_exec(argv, envp);
// }

// void	childp(char **argv, int *pipe_fd, char **env)
// {
// 	int	infile;

// 	infile = open(argv[1], O_RDONLY, 0777);
// 	if (infile == -1)
// 	{
//         // close(pipe_fd[0]);
//         // close(pipe_fd[1]);
// 		perror("Error Infile");
// 		exit(1);
// 	}
// 	dup2(infile, STDIN_FILENO);
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	close(pipe_fd[0]);
// 	close(infile);
// 	execute(argv[2], env);
// }

// void	parentp(char **argv, int *pipe_fd, char **env)
// {
// 	int	outfile;

// 	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (outfile == -1)
// 	{
// 		perror("Error Outfile");
// 		exit(1);
// 	}
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	dup2(outfile, STDOUT_FILENO);
// 	close(pipe_fd[1]);
// 	close(outfile);
// 	execute(argv[3], env);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	int		status;

// 	status = 1;
// 	if (argc != 5)
// 	{
// 		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
// 		exit(1);
// 	}
// 	if (pipe(pipe_fd) == -1)
// 		return (perror("Error pipe"), 1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("Error Fork"), 1);
// 	if (pid == 0)
// 		childp(argv, pipe_fd, env);
// 	else
// 	{
//         waitpid(pid, NULL, 0);
// 		parentp(argv, pipe_fd, env);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 	}
// 	return (0);
// }

// void	childp(char **argv, int *pipe_fd, char **env, int infile)
// {
//     if (infile == -1)
//     {
//         close(pipe_fd[0]);
//         close(pipe_fd[1]);
//         exit(1);
//     }
//     dup2(infile, STDIN_FILENO);
//     dup2(pipe_fd[1], STDOUT_FILENO);
//     close(pipe_fd[0]);
//     close(infile);
//     execute(argv[2], env);
// }

// void	parentp(char **argv, int *pipe_fd, char **env, int infile)
// {
//     int    outfile;

//     outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
//     if (outfile == -1)
//     {
//         perror("Error Outfile");
//         exit(1);
//     }
//     if (infile == -1)
//     {
//         close(pipe_fd[0]);
//         close(pipe_fd[1]);
//         perror("Error Infile");
//     }
//     dup2(pipe_fd[0], STDIN_FILENO);
//     dup2(outfile, STDOUT_FILENO);
//     close(pipe_fd[1]);
//     close(outfile);
//     execute(argv[3], env);
// }

// int    main(int argc, char **argv, char **env)
// {
//     int        pipe_fd[2];
//     pid_t    pid;
//     int        status;

//     status = 1;
//     if (argc != 5)
//     {
//         ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
//         exit(1);
//     }
//     int    infile;

//     infile = open(argv[1], O_RDONLY, 0777);
//     if (pipe(pipe_fd) == -1)
//         return (perror("Error pipe"), 1);
//     pid = fork();
//     if (pid == -1)
//         return (perror("Error Fork"), 1);
//     if (pid == 0)
//         childp(argv, pipe_fd, env, infile);
//     else
//     {
//         if (infile != -1)
//         {
//             parentp(argv, pipe_fd, env, infile);
//             waitpid(pid, NULL, 0);
//             if (WIFEXITED(status))
//                 return (WEXITSTATUS(status));
//         }
//         else
//             parentp(argv, pipe_fd, env, infile);
//             waitpid(pid, NULL, 0);
//             if (WIFEXITED(status))
//                 return (WEXITSTATUS(status));
//     }
//     return (0);
// }
