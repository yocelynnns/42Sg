/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:51:37 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/18 19:44:29 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (src[count])
	{
		count++;
	}
	if (size < 1)
	{
		return (count);
	}
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (count);
}

/* int main()
{
	char dst[10] = "";
	char src[10] = "Hello";
    //char dst1[10] = "Hello";
	//char src1[10] = " world";

    printf("Original str: %s\n", src);
    //printf("Original str (o): %s\n", src1);

    ft_strlcpy(dst, src, 4);
	//strlcpy(dst, src1, 4);

	printf("strlcpy: %s\n", dst);
    //printf("strlcpy (o): %s\n", dst1);
}  */
