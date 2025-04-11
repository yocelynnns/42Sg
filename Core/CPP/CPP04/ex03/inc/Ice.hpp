/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:30 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 00:00:33 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Ice : public AMateria {
public:
    Ice();
    Ice(const Ice& other);
    Ice& operator=(const Ice& other);
    ~Ice();

    AMateria* clone() const;
    void use(ICharacter& target);
};

#endif
