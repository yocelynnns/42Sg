/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:34:15 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/18 19:52:51 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strchr(const char *s, int c)
{
	char	*temp;
	int		i;
	
	temp = (char*)s;
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
