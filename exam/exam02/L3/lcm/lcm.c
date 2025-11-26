/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:54:28 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/08/21 01:57:00 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

unsigned int lcm (unsigned int a, unsigned int b)
{
    unsigned int n;

    if (a == NULL || b == NULL)
        return (0);
    if (a > b)
        n = a;
    else
        n = b;
    
    while (1)
    {
        if (n % a == 0 && n % b == 0)
            return (n);
        ++n;
    }
}