/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:09:12 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/18 20:35:46 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	int count;
	
	count = 0;
	count += write (1, &c, 1);
	return (count);
}

int	ft_putstr(const char *s)
{
	int count;
	int i;

	count = 0;
	i = 0;
	if (!s[i])
		s = "(NULL)";
	while (s[i] != '\0')
		count += write (1, &s[i++], 1);
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	char	*temp;
	int		i;

	c = (unsigned char)c;
	temp = (char *)s;
	i = 0;
	while (*(temp + i))
	{
		if (*(temp + i) == c)
			return (temp + i);
		i++;
	}
	if (c == '\0')
		return (temp + i);
	return (0);
}
