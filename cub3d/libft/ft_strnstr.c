/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:16:32 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/04/22 16:18:39 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//big = str, little = find
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*bg;
	// char			*ltl;

	bg = (char *)big;
	// ltl = (char *)little;
	i = 0;
	if (*little == '\0')
		return (bg);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j < len))
		{
			if (little[j + 1] == '\0')
				return (bg + i);
			j++;
		}
		i++;
	}
	return (0);
}

/* int	main()
{
	size_t len = 10;
	char big[20] = "hello singapore";
	char little[15] = "ng";
	char *result = strnstr(big, little, len);
	if (result)
	{
		printf("%s\n", result);
	}
	else
	{
		printf("Not found\n");
	}
	return (0);
} */
