/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:13:52 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/21 02:02:25 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void writenum(int n)
{
    char num[10] = "0123456789";
    
    while (n >= 10)
        writenum(n / 10);
    write (1, &num[n % 10], 1);
}

int main(int argc, char **argv)
{
    (void)argv;
    
    if (argc > 1)
    {
        writenum(argc - 1);
    }
    write (1, "\n", 1);
}