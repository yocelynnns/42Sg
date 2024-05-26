/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:15:16 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/13 18:19:25 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*int main()
{
    // Test characters
    int testChars[] = {32, 126, 31, 127, 'A', 'z', '0', '9', '!', ' '};
    int numTests = sizeof(testChars) / sizeof(testChars[0]);

    // Test each character and print the result
    for (int i = 0; i < numTests; i++) {
        int ch = testChars[i];
        int result = isprint(ch);
        printf("isprint(%d) = %d\n", ch, result);
    }

    return 0;
}*/