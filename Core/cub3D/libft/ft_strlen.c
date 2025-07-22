/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:19:39 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/19 21:19:56 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*int main() {
    // Test strings
    const char *testStr1 = "Hello, world!";
    const char *testStr2 = "OpenAI";
    const char *testStr3 = "";

    // Calculate lengths using our strlen function
    size_t len1 = strlen(testStr1);
    size_t len2 = strlen(testStr2);
    size_t len3 = strlen(testStr3);

    // Print results
    printf("Length of \"%s\" is %zu\n", testStr1, len1);
    printf("Length of \"%s\" is %zu\n", testStr2, len2);
    printf("Length of \"%s\" is %zu\n", testStr3, len3);

    return 0;
}*/