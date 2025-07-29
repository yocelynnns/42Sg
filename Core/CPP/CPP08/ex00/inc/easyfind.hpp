/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:56:41 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/07/29 16:25:25 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>  // std::find
#include <iterator>   // std::begin, std::end
#include <stdexcept>  // std::runtime_error

template <typename T>
typename T::iterator easyfind(T& container, int val)
{
    typename T::iterator it = std::find(container.begin(), container.end(), val);
    if (it == container.end())
        throw std::runtime_error("Value not found in container.");
    return it;
}

#endif
