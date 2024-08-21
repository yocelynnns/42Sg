/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:07:11 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/20 19:02:30 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_atoi(char *nbr)
{
    int res = 0;

    while (*nbr)
    {
        res = res * 10;
        res = res + *nbr++ -'0';
    }
    return (res);
}

int primenum(int n)
{
    int i = 2;

    if (n <= 1)
        return (0);
    while (i * i <= n)
    {
        if (n % i == 0)
            return (0);
        i++;
    }
    return (1);
}

void writenum(int n)
{
    char nbr[10] = "0123456789";

    if (n >= 10)
        writenum(n / 10);
    write (1, &nbr[n % 10], 1);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
       int nbr = ft_atoi(argv[1]);
       int sum = 0;
       
       while (nbr > 0)
       {
            if (primenum(nbr))
                sum += nbr;
            nbr--;
       }
       writenum(sum); 
    }
    if (argc != 2)
        writenum(0);
    write (1, "\n", 1);
    return (0);
}