/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:13:52 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/06 19:14:35 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void putnbr(int n)
{
    char num;
    while (n >= 10)
        putnbr(n / 10);
    num = (n  % 10) + '0';
    write (1, &num, 1);
}

int main(int argc, char **argv)
{
    (void)argv;

    putnbr(argc - 1);
    write (1, "\n", 1);
    return (0);
}