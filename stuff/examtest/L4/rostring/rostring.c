/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:25:57 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/06 16:45:11 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void firstword(char *start, char *end)
{
    while (start < end)
    {
        write (1, start, 1);
        start++;
    }
}

int main(int argc, char **argv)
{
    char *str;
    char *fwstart;
    char *fwend;
    
    if (argc > 1)
    {
        str = argv[1];
        while (*str == ' ' || *str == '\t')
            str++;
        fwstart = str;
        while ((*str) && (*str != ' ' && *str != '\t'))
            str++;
        fwend = str;
        while (*str == ' ' || *str == '\t')
            str++;
        if (*str)
        {
            while (*str)
            {
                if (*str == ' ' || *str == '\t')
                {
                    while (*str == ' ' || *str == '\t')
                        str++;
                    if (*str)
                        write (1, " ", 1);
                }
                else
                {
                        write (1, str, 1);
                        str++;
                }
            }
            write (1, " ", 1);
        }
        firstword(fwstart, fwend);
    }
    write (1, "\n", 1);    
}