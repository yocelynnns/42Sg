/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:42:16 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/04 20:26:59 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_line(int fd, char *str, char *remain)
{
    int readcheck;
    char *temp;

    readcheck = 1;
    while (readcheck)
    {
        readcheck = read(fd, str, BUFFER_SIZE);
        if (readcheck == -1)
            return (NULL);
        else if (readcheck == 0)
            break;
        str[readcheck] = '\0';
        temp = remain;
        remain = ft_strjoin(temp, str);
        if (!remain)
            return (NULL);
        free(temp);
        if (ft_strchr(str, '\n'))
            break;
    }
    return (remain);
}

static char *get_line(char *peepoo)
{
    char *temp;
    int lkoh;

    lkoh = 0;
    while (peepoo[lkoh] != '\0' && peepoo[lkoh] != '\n')
        lkoh++;
    if (peepoo[lkoh] == '\0')
        return (NULL);
    temp = ft_substr(peepoo, lkoh + 1, ft_strlen(peepoo) - 1);
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
    static char *remain;
    char *peepoo;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!str)
        return (NULL);
    remain = read_line(fd, str, remain);
    free(str);
    if (!remain)
        return (NULL);
    peepoo = ft_substr(remain, 0, ft_strlen(remain));
    remain = get_line(remain);
    return (peepoo);
}

