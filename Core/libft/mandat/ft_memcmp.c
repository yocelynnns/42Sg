/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:39:17 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/18 19:48:30 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
		n--;
	}
	return (0);
}

/* int main()
{
    char s1[20] = "Hello"; 
    char s2[20] = "Hallo";
    size_t n = 3;
    size_t result = ft_memcmp (s1, s2, n);

    printf("The first string: %s\n", s1);
    printf("The second string: %s\n", s2);
    printf("Comparison result = %zu\n", result);
    
    return 0;
}  */
