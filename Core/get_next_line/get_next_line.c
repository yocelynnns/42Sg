/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:37:34 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/13 20:25:16 by ysetiawa         ###   ########.fr       */
=======
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:37:34 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/12 02:14:59 by marvin           ###   ########.fr       */
>>>>>>> 9036cc03042a4babcfb9cb9e3faa1052bcc6b4a3
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

<<<<<<< HEAD
static char	*read_line(int fd, char *buf, char *remain)
{
	int		readcheck;
	char	*temp_buf;
=======
static char	*read_line(int fd, char *str, char *remain)
{
	int		readcheck;
	char	*temp;
>>>>>>> 9036cc03042a4babcfb9cb9e3faa1052bcc6b4a3

	readcheck = 1;
	while (readcheck)
	{
<<<<<<< HEAD
		readcheck = read(fd, buf, BUFFER_SIZE);
=======
		readcheck = read(fd, str, BUFFER_SIZE);
>>>>>>> 9036cc03042a4babcfb9cb9e3faa1052bcc6b4a3
		if (readcheck == -1)
			return (0);
		else if (readcheck == 0)
			break ;
<<<<<<< HEAD
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
=======
		str[readcheck] = '\0';
		if (!remain)
			remain = ft_strdup("");
		temp = remain;
		remain = ft_strjoin(temp, str);
		free (temp);
		temp = NULL;
		if (!remain)
			return (NULL);
		if (ft_strchr(str, '\n'))
>>>>>>> 9036cc03042a4babcfb9cb9e3faa1052bcc6b4a3
			break ;
	}
	return (remain);
}

<<<<<<< HEAD
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
=======
static char	*get_line(char *peepoo)
{
	char	*temp;
	int		lkoh;

	lkoh = 0;
	while (peepoo[lkoh] != '\0' && peepoo[lkoh] != '\n')
		lkoh++;
	if (peepoo[lkoh] == '\0')
		return (NULL);
	temp = ft_substr(peepoo, lkoh + 1, ft_strlen(peepoo) - lkoh);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	peepoo[lkoh + 1] = '\0';
	return (temp);
}

char *get_next_line(int fd)
{
    char *str;
    char *peepoo;
    static char *remain = NULL;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!str)
        return (handle_memory_error(&remain));

    peepoo = read_line(fd, str, remain);
    free(str);

    if (!peepoo)
        return (handle_read_error(&remain));

    remain = get_line(peepoo);
    char *temp = ft_strdup(peepoo);
    free(peepoo);

    if (!temp)
        return (handle_memory_error(&remain));

    return (temp);
}

static char *handle_memory_error(char **remain)
{
    if (*remain)
    {
        free(*remain);
        *remain = NULL;
    }
    return (NULL);
}

static char *handle_read_error(char **remain)
{
    if (*remain)
    {
        free(*remain);
        *remain = NULL;
    }
    return (NULL);
}
>>>>>>> 9036cc03042a4babcfb9cb9e3faa1052bcc6b4a3
