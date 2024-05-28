/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:49:38 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/28 21:52:32 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	checkset(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;
	char	*trimmed;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && checkset(s1[start], set))
		start++;
	while (end > start && checkset(s1[end - 1], set))
		end--;
	len = end - start;
	trimmed = (char *)malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (0);
	i = 0;
	while (i < len)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[len] = '\0';
	return (trimmed);
}

/* int main() {
    char s1[] = "   Hello, world!   ";
    char set[] = " ";
    char *trimmed = ft_strtrim(s1, set);

    printf("Original string: '%s'\n", s1);
    printf("Trimmed string: '%s'\n", trimmed);
    free(trimmed);

    return 0;
} */
