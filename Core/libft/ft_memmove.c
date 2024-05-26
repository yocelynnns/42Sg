/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:57:04 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/24 14:11:05 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == src || n == 0)
		return (dest);
	else if (dest > src)
	{
		while (n-- > 0)
			d[n] = s[n];
		return (dest);
	}
	else //dest < src
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
		return (dest);
	}
}

/* int main() {
    char src[50] = "Learningisfun";
    char src1[50] = "Learningisfun";
    //char dest[50];

    printf("Source before memmove: %s\n", src);
    printf("Source before memmove (o): %s\n", src1);
    
    ft_memmove(src + 8, src, 10);
    memmove(src1 + 8, src1, 10);
    
    printf("Destination after memmove: %s\n", src);
    printf("Destination after memmove (o): %s\n", src1);

    return 0;
} */

/* int main() {
    // Source and destination arrays
    char src1[50] = "Hello, this is a test for memmove function.";
    char dest1[50];
    char src2[50] = "1234567890";
    char dest2[50];
    char src3[50] = "Test";
    char dest3[50];
    char src4[50] = "Hello, World!";
    char dest4[50];

    // Test case 1: Move 6 characters from src1 to dest1
    memmove(dest1, src1, 6);
    printf("Test case 1:\nSource: %s\nDestination: %s\n\n", src1, dest1);

    // Test case 2: Move 4 characters from src2 to dest2
    memmove(dest2, src2, 4);
    printf("Test case 2:\nSource: %s\nDestination: %s\n\n", src2, dest2);

    // Test case 3: Move 3 characters from src3 to dest3
    memmove(dest3, src3, 3);
    printf("Test case 3:\nSource: %s\nDestination: %s\n\n", src3, dest3);

    // Test case 4: Move 0 characters from src4 to dest4
    memmove(dest4, src4, 0);
    printf("Test case 4:\nSource: %s\nDestination: %s\n\n", src4, dest4);

    return 0;
} */
