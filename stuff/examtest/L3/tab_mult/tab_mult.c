/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:37:59 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 10:55:51 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_atoi(char *str)
{
    int sign = 1;
    int res = 0;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    while (*str == '+' || *str == '-')
    {
        if (*str == '-')
        {
            sign = -1;
            str++;
        }
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + *str - '0';
        str++;
    }
    return (res * sign);
}

void ft_putchar(char c)
{
    write (1, &c, 1);
}

void ft_putnbr(int n)
{
    if (n >= 10)
        ft_putnbr(n / 10);
    ft_putchar(n % 10 + '0');
}

int main(int argc, char **argv)
{
    int i;
    int nbr;

    if (argc != 2)
        write (1, "\n", 1);
    else
    {
        i = 1;
        nbr = ft_atoi(argv[1]);
        while (i <= 9)
        {
            ft_putnbr(i);
            write (1, " x ", 3);
            ft_putnbr(nbr);
            write(1, " = ", 3);
			ft_putnbr(i * nbr);
			write(1, "\n", 1);
			i += 1;
        }
    }
}