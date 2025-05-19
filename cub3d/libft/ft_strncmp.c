/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:10:02 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/28 19:40:25 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n)
		i++;
	if (i == n || s1[i] == s2[i])
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* int main() {
    char s1[20] = "test\200"; 
    char s2[20] = "test\0";
    size_t n = 6;
    size_t result = ft_strncmp (s1, s2, n);
    size_t result2 = strncmp (s1, s2, n);

    printf("The first string: %s\n", s1);
    printf("The second string: %s\n", s2);
    printf("Comparison result = %zu\n", result);
    printf("Expected = %zu\n",result2);
    
    return 0;
}  */