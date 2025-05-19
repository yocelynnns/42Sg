/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:59:21 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/24 14:11:56 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int chr)
{
	char	*temp;
	size_t	i;

	temp = (char *)str;
	i = ft_strlen(str);
	if (chr == '\0')
		return (temp + i);
	while (i != 0)
	{
		if (temp[i] == (char)chr)
			return (temp + i);
		i--;
	}
	if (str[0] == (char)chr)
		return (temp);
	return (0);
}

/* int main() {
    char str[] = "Hello, World!";
    int chr = 'o';
    
    printf("The original string is '%s'\n", str);
    
    // Demonstrate strrchr
    char *last_occurrence = ft_strrchr(str, chr);
    if (last_occurrence) {
        printf("The last occurrence of is: '%s'\n", last_occurrence);
    } else {
        printf("The character '%c' is not found in the string '%s'\n", chr, str);
    }
    
    return 0;
}  */
