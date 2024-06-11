/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:37:34 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/12 02:14:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *str, char *remain)
{
	int		readcheck;
	char	*temp;

	readcheck = 1;
	while (readcheck)
	{
		readcheck = read(fd, str, BUFFER_SIZE);
		if (readcheck == -1)
			return (0);
		else if (readcheck == 0)
			break ;
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
			break ;
	}
	return (remain);
}

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
