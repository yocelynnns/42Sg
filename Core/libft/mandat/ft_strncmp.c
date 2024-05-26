/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:10:02 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/14 15:42:51 by ysetiawa         ###   ########.fr       */
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
		return (s1[i] - s2[i]);
}

/* int main() {
    char s1[20] = "Hello"; 
    char s2[20] = "Hallo";
    size_t n = 3;
    size_t result = ft_strncmp (s1, s2, n);

    printf("The first string: %s\n", s1);
    printf("The second string: %s\n", s2);
    printf("Comparison result = %zu\n", result);
    
    return 0;
} */