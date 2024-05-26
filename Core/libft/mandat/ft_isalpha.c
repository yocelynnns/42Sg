/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:34 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/13 18:09:37 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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
        int result = isalpha(ch);
        printf("isalpha('%c') = %d\n", ch, result);
    }

    return 0;
}*/
