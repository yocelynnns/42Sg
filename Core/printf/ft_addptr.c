/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:10:19 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/18 21:15:23 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int ft_putptr_hex(unsigned long long n)
{
    int count;
    const char *base;
    
    count = 0;
    base = "0123456789abcdef";
    if (n >= 16)
        count += ft_putptr_hex(n / 16);
    count += ft_putchar(base[n % 16]);
    return (count);
}

int ft_putaddress(void *ptr)
{
    int count;
    
    count = 0;
    count += ft_putstr("0x");
    count += ft_putptr_hex((unsigned long long)ptr);
    return (count);
}
