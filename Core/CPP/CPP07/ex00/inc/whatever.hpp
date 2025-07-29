/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:48:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/23 12:21:29 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

template <typename Type>
void swap(Type& val1, Type& val2)
{
    Type temp;
    temp = val1;
    val1 = val2;
    val2 = temp; 
}

template <typename Type>
Type min(const Type& val1, const Type& val2)
{
    if (val1 < val2)
        return val1;
    return val2;
}

template <typename Type>
Type max(const Type& val1, const Type& val2)
{
    if (val1 > val2)
        return val1;
    return val2;
}

#endif
