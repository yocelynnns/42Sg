/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:13:39 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/23 13:22:11 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename Type, typename Func>
void iter(Type* arr, size_t len, Func func)
{
    size_t i = 0;
    while (i < len)
    {
        func(arr[i]);
        ++i;
    }
}

#endif
