/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:31:13 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 10:36:21 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void writeword(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        if ((str[i] >= 'a' && str[i] <= 'z') && (str[i - 1] == ' ' \
            || str[i - 1] == '\t' || str[i - 1] == 0))
            str[i] -= 32;
        write (1, &str[i], 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    int i;

    if (argc == 1)
        write (1, "\n", 1);
    else
    {
        i = 1;
        while (i < argc)
        {
            writeword(argv[i]);
            write (1, "\n", 1);
            i++;
        }
    }
    return (0);
}