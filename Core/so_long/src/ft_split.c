/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:54:49 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/22 01:11:57 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	wordlen(const char *s, char c)
{
	int	i;
	int	wlen;

	i = 0;
	wlen = 0;
	while (s[i] && s[i] != c)
	{
		wlen++;
		i++;
	}
	return (wlen);
}

char	*writeword(char const *s, int len)
{
	char	*word;
	int		i;

	if (len == 0)
		return (NULL);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (0);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

char	**split_words(const char *s, char c, int word_count)
{
	char	**result;
	int		i;
	int		j;

	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			result[j] = writeword(s + i, wordlen(s + i, c));
			if (!result[j])
				return (free_array(result, j));
			i += wordlen(s + i, c);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int	word_count;
	int	i;

	if (!s)
		return (0);
	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (!(s[i] == c) && ((s[i + 1] == c) || !(s[i + 1])))
			word_count++;
		i++;
	}
	return (split_words(s, c, word_count));
}

// int main()
// {
//     char str[] = "  this is  a string ";
//     char **result = ft_split(str, ' ');

//     if (result != NULL)
//     {
//         int i = 0;
//         while (result[i] != NULL)
//         {
//             printf("%s\n", result[i]);
//             free(result[i]);
//             i++;
//         }
//         free(result);
//     }
//     else
//         printf("Memory allocation failed or empty string\n");
//     return 0;
// }
