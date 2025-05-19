/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:34:15 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/28 21:03:34 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

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

/* int main(void)
{
    const char *str = "Hello, world!";
    char c = 'w';
    char *result;

    result = ft_strchr(str, c);
    if (result)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("NULL\n");
    }

    return 0;
} */
