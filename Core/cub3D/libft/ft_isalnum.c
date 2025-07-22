/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:46:36 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/13 18:09:14 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

/*int main()
{
    // Test characters
    char testChars[] = {'A', 'z', '0', '9', '!', ' ', '@', 'G', 'm', '3'};
    int numTests = sizeof(testChars) / sizeof(testChars[0]);

    // Test each character and print the result
    for (int i = 0; i < numTests; i++) {
        char ch = testChars[i];
        int result = ft_isalnum(ch);
        printf("isalnum('%c') = %d\n", ch, result);
    }

    return 0;
}*/