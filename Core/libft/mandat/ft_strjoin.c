/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:55:40 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/24 15:56:11 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char) * \
			((ft_strlen(s1) + ft_strlen(s2)) + 1));
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

/* int main()
{
    char s1[20] = "Hello"; 
    char s2[20] = "World";
    char *result = ft_strjoin (s1, s2);
	
    printf("The first string: %s\n", s1);
    printf("The second string: %s\n", s2);
    printf("Join string = %s\n", result);
    
    return (0);
}*/
