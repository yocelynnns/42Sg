/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:41:56 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/24 20:41:56 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ptrhex(unsigned long long n)
{
	int			count;
	const char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_ptrhex(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_putaddr(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	count += ft_putstr("0x");
	count += ft_ptrhex((unsigned long long)ptr);
	return (count);
}

