/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:35:39 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/15 21:28:06 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>

void	execute(char *argv, char **envp);
char	*find_path(char *cmd, char **envp);
void    childp(char **argv, int *pipe_fd, char **env);
void    parentp(char **argv, int *pipe_fd, char **env);
int	main(int argc, char **argv, char **env);
void	ft_putstr_fd(char *s, int fd);
int	wordlen(const char *s, char c);
char	*writeword(char const *s, int len);
char	**free_array(char **ptr, int i);
char	**split_words(const char *s, char c, int word_count);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

#endif