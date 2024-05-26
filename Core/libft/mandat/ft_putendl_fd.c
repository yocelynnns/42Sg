/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:23:02 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/25 18:50:50 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putendl_fd(char *s, int fd)
{
    if (!s || !fd)
        return ;
    write (fd, s, ft_strlen(s));
    write (fd, "\n", 1);
}

// #include <sys/stat.h>
// #include <fcntl.h>

// int main()
// { 
//     int fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
//     ft_putendl_fd("hello", fd);
//     return (0);
// }