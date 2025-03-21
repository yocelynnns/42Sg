/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:23:51 by hthant            #+#    #+#             */
/*   Updated: 2025/02/18 22:44:15 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n);

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
		{
			return ((unsigned char *)(s + i));
		}
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*i = ft_memchr("hello",'e',5);
// 	char	*j = memchr("HELLO",'E',5);
// 	printf("%s\n%s\n",i,j);
// }
