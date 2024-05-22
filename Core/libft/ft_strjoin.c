/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:41:12 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/21 15:41:21 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    int  i;
    int  j;
    int  len;
    char    *join;

    if (!s1 || !s2)
        return (NULL);
    len = ft_strlen(s1) + ft_strlen(s2);
    join = (char *)malloc(sizeof(char) * len + 1);

    i = 0;
    j = 0;
    if (!join)
        return (NULL);
    while (s1[i])
    {
        join[i] = s1[i]; 
        i++;
    }
    while (s2[j])
    {
        join[i] = s2[j];
        i++;
        j++;
    }
    join[i] = '\0';
    return (join);
}

