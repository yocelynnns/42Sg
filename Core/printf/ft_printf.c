/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:54:27 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/18 14:26:33 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int  ft_format(va_list args, const char format)
{
    if (format == 'c')
        return ft_putchar(va_arg(args, int));
    else if (format == 's')
        return ft_putstr(va_arg(args, char *));
    else if (format == 'd' || format == 'i')
        return ft_putnbr(va_arg(args, int));
    else if (format == 'X' || format == 'x')
        return ft_puthex(va_arg(args, unsigned int), format);
    else if (format == 'p')
        return ft_putaddr(va_arg(args, void *));
    else if (format == 'u')
        return ft_putunsign(va_arg(args, unsigned int));
    else if (format == '%')
        return ft_putchar('%');
    else
        return (-1);
}

int ft_printf(const char *str, ...)
{
    va_list args;
    int     i;
    int     len;
    
    i = 0;
    len = 0;
    va_start(args, str);
    while (*(str + i)) {
        if (*(str + i) == '%' && ft_strchr("cspdiuxX%", *(str + i + 1)))
        {
            len += ft_format(args, *(str + i + 1));
            i++;
        }
        else
            len += ft_putchar(*(str + i));
        i++;
    }
    va_end(args);
    return len;
}
