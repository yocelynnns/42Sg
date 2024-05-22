/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:38:41 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/14 17:54:51 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == 32))
	{
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
		{
			sign *= -1;
		}
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

/*int main()
{
    // Test strings
    const char *testStr1 = "1234";
    const char *testStr2 = "-5678";
    const char *testStr3 = "   42";
    const char *testStr4 = "   -42";
    const char *testStr5 = "+987";
    const char *testStr6 = "0";
	const char *testStr7 = "   ++--123";
    const char *testStr8 = "abc";  // This should result in 0 as per atoi behavior
    const char *testStr9 = "  +abc";  // This should also result in 0

    // Convert strings to integers using our atoi function
    int num1 = atoi(testStr1);
    int num2 = atoi(testStr2);
    int num3 = atoi(testStr3);
    int num4 = atoi(testStr4);
    int num5 = atoi(testStr5);
    int num6 = atoi(testStr6);
    int num7 = atoi(testStr7);
    int num8 = atoi(testStr8);
	int num9 = atoi(testStr9);

    // Print results
    printf("String \"%s\" to integer is %d\n", testStr1, num1);
    printf("String \"%s\" to integer is %d\n", testStr2, num2);
    printf("String \"%s\" to integer is %d\n", testStr3, num3);
    printf("String \"%s\" to integer is %d\n", testStr4, num4);
    printf("String \"%s\" to integer is %d\n", testStr5, num5);
    printf("String \"%s\" to integer is %d\n", testStr6, num6);
    printf("String \"%s\" to integer is %d\n", testStr7, num7);
    printf("String \"%s\" to integer is %d\n", testStr8, num8);
	printf("String \"%s\" to integer is %d\n", testStr9, num9);

    return 0;
}*/
