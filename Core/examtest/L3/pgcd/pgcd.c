/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:51:54 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/06 19:08:32 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n1;
    int n2;

    if (argc == 3)
    {
        if ((n1 = atoi(argv[1])) > 0 && (n2 = atoi(argv[2])) > 0)
        {
            while (n1 != n2)
            {
                if (n1 > n2)
                    n1 -= n2;
                else
                    n2 -= n1;
            }
            printf("%d", n1);
        }
    }
    printf ("\n");
}