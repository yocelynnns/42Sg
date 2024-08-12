/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:39:33 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/12 17:58:59 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char ft_strncpy(char *s1, char *s2, int n)
{
    int i = -1;
    while (++i < n && s2[i])
        s1[i] = s2[i];
    s1[i] = '\0';
    return (s1);
}

char **ft_split(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int wc = 0;

    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
        if (str[i])
            wc++;
        while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
            i++;
    }
    char **res = (char **)malloc(sizeof(char *) * (wc + 1));
    i = 0;
    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
        j = i;
        while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
            i++;
        if (i < j)
        {
            res[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
            ft_strncpy(res[k++], &str[j], i - j);
        }
    }
    res[k] = '\0';
    return (res);
}