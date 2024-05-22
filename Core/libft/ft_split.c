/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:03 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/22 21:33:12 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	countw(const char *s, char c)
{
	size_t count;
    int flag;
    
    count = 0;
    flag = 0; // to track if its a word
	while (*s)
	{
		if (*s != c && !flag) // start of a word
		{
			count++;
			flag = 1; // flag as a word
		}
		else if (*s == c) 
			flag = 0; // reset the flag
		s++;
	}
	return (count);
}

char **ft_split(char const *s, char c)
{
    size_t count;
    char **result;
    size_t i;
    
    if (!s)
		return (NULL);
    
    count = countw(s, c);
    result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			const char *start;
            
            start = s; // start
			while (*s && *s != c)
				s++;
			size_t word_length = s - start;
			result[i] = ft_substr(start, 0, word_length);
			if (!result[i])
			{
				while (i > 0)
					free(result[--i]);
				free(result);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}