/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:13:55 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/25 17:32:23 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putstr_fd(char *s, int fd)
{
    if (!s || !fd)
        return ;
    write (fd, s, ft_strlen(s));
}

// #include <sys/stat.h>
// #include <fcntl.h>

// int main()
// { 
//     int fd = open("test.txt", O_WRONLY);
//     ft_putstr_fd("hello", fd);
// }