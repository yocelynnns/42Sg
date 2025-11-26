/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:49:35 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/24 20:49:35 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'X' || format == 'x')
		return (ft_puthex(va_arg(args, unsigned int), format));
	else if (format == 'p')
		return (ft_putaddr(va_arg(args, void *)));
	else if (format == 'u')
		return (ft_putunsign(va_arg(args, unsigned int)));
	else if (format == '%')
		return (ft_putchar('%'));
	else
		return (-1);
}

int	checkchar(const char *str, int i)
{
	if (*(str + i + 1) != 'c' && *(str + i + 1) != 's'
		&& *(str + i + 1) != 'd' && *(str + i + 1) != 'x'
		&& *(str + i + 1) != 'X' && *(str + i + 1) != 'i'
		&& *(str + i + 1) != 'p' && *(str + i + 1) != 'u'
		&& *(str + i + 1) != '%')
		return (1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (*(str + i))
	{
		if (*(str + i) == '%' && checkchar(str, i))
		{
			len = -1;
			break ;
		}
		else if (*(str + i) == '%' && ft_strchr("cspdiuxX%", *(str + i + 1)))
		{
			len += ft_format(args, *(str + i + 1));
			i++;
		}
		else
			len += ft_putchar(*(str + i));
		i++;
	}
	va_end(args);
	return (len);
}

// int main()
// {
//     char c = 'A';
//     char *str = "Hello, world!";
//     int num = 42;
//     int neg = -100;
//     unsigned int hex = 123456789;

//     ft_printf("%%c: %c\n", c);
//     ft_printf("%%s: %s\n", str);
//     ft_printf("%%p: %p\n", str);
//     ft_printf("%%d: %d\n", num);
//     ft_printf("%%i: %i\n", num);
//     ft_printf("%%u: %u\n", neg);
//     ft_printf("%%x: %x\n", hex);
//     ft_printf("%%X: %X\n", hex);
// 	ft_printf("%%\n");

// 	printf("----------\n");
// 	printf("%%c: %c\n", c);
//     printf("%%s: %s\n", str);
//     printf("%%p: %p\n", str);
//     printf("%%d: %d\n", num);
//     printf("%%i: %i\n", num);
//     printf("%%u: %u\n", neg);
//     printf("%%x: %x\n", hex);
//     printf("%%X: %X\n", hex);
// 	printf("%%\n");

// 	return (0);
// }

// int main(){
// 	int a = ft_printf("%");
// 	printf("a: %d\n", a);
// }