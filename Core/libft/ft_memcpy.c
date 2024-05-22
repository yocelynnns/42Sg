/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:07:13 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/18 19:48:56 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}

/* int main()
{
    char src[50] = "Geekfor";
    char src1[50] = "Geekfor";
    //char dest[50];
    //char dest1[50];

    printf("Source before memcpy: %s\n", src);
    printf("Source before memcpy (o): %s\n", src1);
    
    size_t n = 4;
    ft_memcpy(src + 3, src, n);
    memcpy(src1 + 3, src1, n); 
    
    printf("Destination after memcpy: %s\n", src);
    printf("Destination after memcpy (o): %s\n", src1);

   // Additional test: Copy part of the array
    char partialDest[20];
    memcpy(partialDest, src, 5);
    partialDest[5] = '\0'; // Null-terminate the string
    printf("Partial destination after memcpy: %s\n", partialDest); 

    return 0;
}  */
