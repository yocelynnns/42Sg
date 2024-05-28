/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:53:37 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/28 21:34:30 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	invert(char *s, unsigned int num, long int len)
{
	while (num > 0)
	{
		s[len--] = 48 + (num % 10);
		num = num / 10;
	}
	return (*s);
}

static long int	countlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*s;
	long int		len;
	unsigned int	num;
	int				sign;

	sign = 1;
	len = countlen(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		sign *= -1;
		num = n * -1;
		s[0] = '-';
	}
	else
		num = n;
	invert(s, num, len - 1);
	s[len] = '\0';
	return (s);
}

/* int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("Length: %ld\nitoa: %s\n", 
		countlen(atoi(argv[1])), ft_itoa(atoi(argv[1])));
	}
	return (EXIT_SUCCESS);
} */

/* int main()
{
    // Test strings
    unsigned int testint1 = 00123;
    unsigned int testint2 = -5678;
    // unsigned int *testint3 = 42;
    // unsigned int *testint4 = -42;
    // unsigned int *testint5 = +987;
    // unsigned int *testint6 = 0;
    
    // Convert strings to integers using our atoi function
    char *char1 = ft_itoa(testint1);
    char *char2 = ft_itoa(testint2);
    // const char3 = ft_itoa(testint3);
    // const char4 = ft_itoa(testint4);
    // const char5 = ft_itoa(testint5);
    // const char6 = ft_itoa(testint6);

    // Print results
    printf("Integer %d to String is %s\n", testint1, char1);
    printf("Integer %d to String is %s\n", testint2, char2);
    // printf("Integer \"%d\" to String is %s\n", testint3, char3);
    // printf("Integer \"%d\" to String is %s\n", testint4, char4);
    // printf("Integer \"%d\" to String is %s\n", testint5, char5);
    // printf("Integer \"%d\" to String is %s\n", testint6, char6);

    return 0;
}   */