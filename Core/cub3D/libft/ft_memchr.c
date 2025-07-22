/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:46:52 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/18 19:55:38 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)str;
	i = 0;
	while (n > i)
	{
		if (temp[i] == (unsigned char)c)
			return (&temp[i]);
		i++;
	}
	return (0);
}

/* int main()
{
    char s1[20] = "Hello"; 
    char s2[20] = "Hello";
	int	c1 = 'e'; 
    int c2 = 'e';
    size_t n = 2;	
    char *result1 = ft_memchr (s1, c1, n);
	char *result2 = memchr (s2, c2, n);

    printf("The first string: %s\n", s1);
	printf("The first string (o): %s\n", s2);
    printf("Found string: %s\n", result1);
	printf("Found string: %s\n", result2);
    
    return 0;
}   */