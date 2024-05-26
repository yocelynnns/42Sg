/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:47:51 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/16 17:56:04 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n > 0)
	{
		*temp = c;
		temp++;
		n--;
	}
	return (s);
}

/* int main () {
   char str[50] = "hello";
   char str2[50] = "hello";

	printf("Source before memset: %s\n", str);
    printf("Source before memset (o): %s\n", str2);
    
    ft_memset(str, '$', 2);
	memset(str2,'$', 2);
    
    printf("Destination after memset: %s\n", str);
    printf("Destination after memset (o): %s\n", str2);
   
   return(0);
} */
