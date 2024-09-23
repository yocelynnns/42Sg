/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:30:30 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/09/23 17:08:48 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		return (0);
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
    if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
        word_count++;
    i++;
}
	return (split_words(s, c, word_count));
}
