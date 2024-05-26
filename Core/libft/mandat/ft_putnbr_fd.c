/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:08:54 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/25 18:53:53 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putnbr_fd(int n, int fd)
{
	char	output[20];

    if (n == -2147483648)
        write (fd, "-2147483648", 11);
    if (n == 0)
    {
        write (fd, "0", 1);
    }
	else if (n < 0)
	{
		write (fd, "-", 1);
		n *= -1;
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
        *output = n + '0';
		write(fd, &output, 1);
	}
}

// #include <sys/stat.h>
// #include <fcntl.h>

// int main()
// { 
//     int fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
//     ft_putnbr_fd(12345, fd);
// }