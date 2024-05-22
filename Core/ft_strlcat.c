/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:10 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:22 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <string.h>
// #include <bsd/string.h>

int main()
{
	char dst[10] = "Hello";
	char src[40] = " world";
/* 	char dst2[10] = "Hello";
	char src2[40] = " world"; */
   
	int size = 10;
	strlcat(dst, src, size + 1);
	printf("strlcat: %s\n", dst);

/* 	ft_strlcat(dst2, src2, size + 1);
	printf("ft_strlcat: %s\n", dst2); */
}
