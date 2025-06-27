/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SearchableBag.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:38:47 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 20:38:52 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLEBAG_HPP
#define SEARCHABLEBAG_HPP

#include "Bag.hpp"

class SearchableBag : public Bag {
public:
    virtual bool has(int value) const = 0;
    virtual ~SearchableBag() {}
};

#endif
