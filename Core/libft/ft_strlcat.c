/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:47:17 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/18 19:57:42 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	iter;
	size_t	tempd;
	size_t	temps;

	iter = 0;
	tempd = ft_strlen(dst);
	temps = ft_strlen(src);
	len = tempd;
	if (size < 1)
		return (temps + size);
	while (src[iter] && len < size - 1)
	{
		dst[len] = src[iter];
		len++;
		iter++;
	}
	dst[len] = '\0';
	if (size < tempd)
		return (temps + size);
	else
		return (tempd + temps);
}

/* int main()
{
    char dest[20] = "Hello";
    const char *src = " World!";
    size_t size = sizeof(dest);

    printf("Initial dest: '%s'\n", dest);
	//printf("Initial dest (o): '%s'\n", dest);

    size_t result = ft_strlcat(dest, src, size);
	//size_t result1 = strlcat(dest, src, size);

    printf("Final dest: '%s'\n", dest);
    printf("Total length: %zu\n", result);
	//printf("Final dest (o): '%s'\n", dest);
    //printf("Total length (o): %zu\n", result1);

    return 0;
}   */
