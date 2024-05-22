/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:37:44 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/21 14:37:46 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t  i;
    char    *d;
    
    if (!s)
        return (NULL);
    if (start >= ft_strlen(s))
        return ("");
    // if ((ft_strlen(s) - start) < len)
    //     len = ft_strlen(s) - start;
    
    d = (char *)malloc(sizeof(char) * (len + 1));
    if (!d)
        return (NULL);

    i = 0;
    while (i < len)
    {
        d[i] = s[start + i];
        i++;
    }
    d[len] = '\0';
    return (d);
}

/* int main()
{
    char s1[20] = "Hello"; 
    size_t start = 4;
    size_t len = 3;
    char *result = ft_substr (s1, start, len);

    printf("The first string: %s\n", s1);
    printf("Found Substring: %s\n", result);
    
    return 0;
}  */