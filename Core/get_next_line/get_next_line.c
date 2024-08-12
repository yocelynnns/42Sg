/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:37:34 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/12 14:52:15 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buf, char *remain)
{
	int		readcheck;
	char	*temp_buf;

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
		temp_buf = remain;
		remain = ft_strjoin(temp_buf, buf);
		if (temp_buf)
			free (temp_buf);
		temp_buf = NULL;
		if (!remain)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (remain);
}

static char	*get_line(char *line)
{
	char	*temp_line;
	int		lkoh;

	lkoh = 0;
	while (line[lkoh] != '\0' && line[lkoh] != '\n')
		lkoh++;
	if (line[lkoh] == '\0')
		return (NULL);
	temp_line = ft_substr(line, lkoh + 1, ft_strlen(line) - lkoh);
	if (!temp_line)
		return (NULL);
	if (temp_line[0] == '\0')
	{
		free(temp_line);
		temp_line = NULL;
		return (NULL);
	}
	line[lkoh + 1] = '\0';
	return (temp_line);
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
	static char	*remain = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (handle_error(&remain));
	line = read_line(fd, buf, remain);
	free(buf);
	if (!line)
		return (handle_error(&remain));
	remain = get_line(line);
	temp = ft_strdup(line);
	free(line);
	if (!temp)
		return (handle_error(&remain));
	return (temp);
}
