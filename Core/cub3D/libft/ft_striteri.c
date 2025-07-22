/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:48:20 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/28 16:45:19 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}

// void	upper(unsigned int i, char *c)
// {
//     i = 0;
//     if (*c >= 'a' && *c <= 'z')
//         *c = *c - 32;
// }

// int main()
// {
//     char str[10] = "hello";
//     ft_striteri(str, upper);
//     printf("%s\n", str);
//     return 0;
// }