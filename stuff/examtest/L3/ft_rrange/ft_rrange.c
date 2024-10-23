/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:45:30 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 01:51:19 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int *ft_rrange(int start, int end)
{
    int i = 0;
    int len = abs((end - start)) + 1;
    int *res = (int *)malloc(sizeof(int) * len);

    while (i < len)
    {
        if (start < end)
        {
            res[i] = end;
            end--;
            i++;
        }
        else
        {
            res[i] = end;
            end++;
            i++;
        }
    }
    return (res);
}

#include <stdio.h>
int main()
{
    int start = -1;
    int end = 2;
    int *range = ft_rrange(start, end);

    for (int i = 0; i < abs(end - start) + 1; i++)
    {
        printf("%d ", range[i]);
    }

    free(range);
    return 0;
}