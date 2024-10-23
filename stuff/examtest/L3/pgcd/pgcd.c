/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:51:54 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/21 02:13:34 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int a;
    int b;
    
    if (argc == 3)
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);

        while (a != b)
        {
            if (a > b)
                a -= b;
            else
                b -= a;
        }
        printf ("%d", a);
    }
    printf ("\n");
}