/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:29:49 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 01:44:49 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int *ft_range(int start, int end)
{
    int i = 0;
    int len = abs((end - start)) + 1;
    int *res = (int *)malloc(sizeof(int) * len);

    while (i < len)
    {
        if (start < end)
        {
            res[i] = start;
            start++;
            i++;
        }
        else
        {
            res[i] = start;
            start--;
            i++;
        }
    }
    return (res);
}

// #include <stdio.h>
// int main()
// {
//     int start = 1;
//     int end = 4;
//     int *range = ft_range(start, end);

//     for (int i = 0; i < abs(end - start) + 1; i++)
//     {
//         printf("%d ", range[i]);
//     }

//     free(range);
//     return 0;
// }