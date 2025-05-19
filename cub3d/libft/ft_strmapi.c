/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:20:12 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/28 17:04:28 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*result;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// char	upper(unsigned int i, char c)
// {
//     i = 0;
//     if (c >= 'a' && c <= 'z')
//         return (c - 32);
//     return (c);
// }

// int main()
// {
//     char *result = ft_strmapi("hello", upper);
//     if (result)
//     {
//         printf("%s\n", result);
//         free(result);
//     }
//     return 0;
// }