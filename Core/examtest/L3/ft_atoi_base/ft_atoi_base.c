/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:01:54 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 11:16:49 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int isvalid(int ch, int baselen)
{
    char *lower = "0123456789abcdef";
    char *upper = "0123456789ABCDEF";
    int i = 0;

    while (i < baselen)
    {
        if (ch == lower[i] || ch == upper[i])
            return (1);
        i++;
    }
    return (0);
}

int ft_atoi_base(const char *str, int str_base)
{
    int res = 0;
    int sign = 1;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    while (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str && isvalid(*str, str_base))
    {
        res *= str_base;
        
        if (*str >= '0' && *str <= '9')
            res += *str - '0';
        else if (*str >= 'a' && *str <= 'z')
            res += *str - 'a' + 10;
        else if (*str >= 'A' && *str <= 'Z')
            res += *str - 'A' + 10;
        str++; 
    }
    return (res * sign);
}


// #include <stdio.h>
// int main()
// {
//     char str[] = "   -1A3";
//     int base = 16;
    
//     printf("%d", ft_atoi_base(str, base));
// }