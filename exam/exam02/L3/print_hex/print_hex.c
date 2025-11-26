/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 02:14:49 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 02:26:34 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_atoi(char *str)
{
    int res = 0;

    while (*str)
    {
        res = res * 10;
        res = res + *str - '0';
        ++str;
    }
    return (res);
}

void printhex(int num)
{
    char hex[] = "0123456789abcdef";

    if (num >= 16)
        printhex(num / 16);
    write(1, &hex[num % 16], 1);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int num = ft_atoi(argv[1]);
        printhex(num);
    }
    write (1, "\n", 1);
}