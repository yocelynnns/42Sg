/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:30:13 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/21 14:30:15 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdup(const char *s)
{
    size_t size;
    char *d;

    size = ft_strlen(s);
    d = (char *)malloc(size * sizeof(char) + 1);
    if (d == NULL)
        return (NULL);
    ft_memcpy(d, s, size);
    d[size] = '\0';
    return (d);
}

/* int main()
{
    char s[20] = "Hello World";
    char s1[20] = "Hello World";
    char *result;
    char *result1;

    result = ft_strdup(s);
    result1 = strdup(s1);

    printf("The first string: %s\n", s);
    printf("The first string (o): %s\n", s1);

    printf("The duplicated string: %s\n", result);
    printf("The duplicated string (o): %s\n", result1);

    free(result);
    free(result1);

    return 0;
} */
