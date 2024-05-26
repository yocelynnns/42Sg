/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:30 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/25 17:13:03 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putchar_fd(char c, int fd)
{
    write (fd, &c, 1);
}

// #include <sys/stat.h>
// #include <fcntl.h>

// int main()
// { 
//     int fd = open("test.txt", O_WRONLY);
//     ft_putchar_fd('H', fd);
// }