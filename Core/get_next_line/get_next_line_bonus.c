/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:29 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/14 17:32:01 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(int fd, char *buf, char *remain)
{
	int		readcheck;
	char	*temp;

	readcheck = 1;
	while (readcheck)
	{
		readcheck = read(fd, buf, BUFFER_SIZE);
		if (readcheck == -1)
			return (0);
		else if (readcheck == 0)
			break ;
		buf[readcheck] = '\0';
		if (!remain)
			remain = ft_strdup("");
		temp = remain;
		remain = ft_strjoin(temp, buf);
		free (temp);
		temp = NULL;
		if (!remain)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (remain);
}

static char	*get_line(char *line)
{
	char	*temp;
	int		lkoh;

	lkoh = 0;
	while (line[lkoh] != '\0' && line[lkoh] != '\n')
		lkoh++;
	if (line[lkoh] == '\0')
		return (NULL);
	temp = ft_substr(line, lkoh + 1, ft_strlen(line) - lkoh);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	line[lkoh + 1] = '\0';
	return (temp);
}

static char	*handle_error(char **remain)
{
	if (*remain)
	{
		free(*remain);
		*remain = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	char		*temp;
	static char	*remain[4096] = {NULL};

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (handle_error(&remain[fd]));
	line = read_line(fd, buf, remain[fd]);
	free(buf);
	if (!line)
		return (handle_error(&remain[fd]));
	remain[fd] = get_line(line);
	temp = ft_strdup(line);
	free(line);
	if (!temp)
		return (handle_error(&remain[fd]));
	return (temp);
}
