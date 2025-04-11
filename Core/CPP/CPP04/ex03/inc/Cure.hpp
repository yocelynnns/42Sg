/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:23 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 00:00:26 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Cure : public AMateria {
public:
    Cure();
    Cure(const Cure& other);
    Cure& operator=(const Cure& other);
    ~Cure();

    AMateria* clone() const;
    void use(ICharacter& target);
};

#endif
