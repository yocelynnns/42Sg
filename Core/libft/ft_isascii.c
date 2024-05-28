/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:10:30 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/18 19:50:10 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*int main()
{
    // Test characters
    int testChars[] = {'A', 'z', '0', '9', '!', ' ', \\
    '@', 'G', 'm', '3', 128, -1, 255};
    int numTests = sizeof(testChars) / sizeof(testChars[0]);

    // Test each character and print the result
    for (int i = 0; i < numTests; i++) {
        int ch = testChars[i];
        int result = isascii(ch);
        printf("isascii(%d) = %d\n", ch, result);
    }

    return 0;
}*/
