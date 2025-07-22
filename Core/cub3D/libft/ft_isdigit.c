/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:44:47 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/13 18:09:22 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*int main()
{
    // Test characters
    char testChars[] = {'0', '5', '9', 'A', 'z', '!', ' ', '7', '3', 'B'};
    int numTests = sizeof(testChars) / sizeof(testChars[0]);

    // Test each character and print the result
    for (int i = 0; i < numTests; i++) {
        char ch = testChars[i];
        int result = isdigit(ch);
        printf("isdigit('%c') = %d\n", ch, result);
    }

    return 0;
}*/