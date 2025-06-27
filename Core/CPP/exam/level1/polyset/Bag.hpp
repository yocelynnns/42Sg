/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bag.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:38:28 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 20:38:33 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BAG_HPP
#define BAG_HPP

class Bag {
public:
    virtual void insert(int value) = 0;
    virtual int size() const = 0;
    virtual void print() const = 0;
    virtual ~Bag() {}
};

#endif
