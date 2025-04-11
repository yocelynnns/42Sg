/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:53:04 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 23:59:25 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>
#include <iostream>
#include "ICharacter.hpp"

class AMateria {
    protected:
        std::string type;
    public:
        // Orthodox Canonical Form
        AMateria();                                // Default constructor
        AMateria(const AMateria& other);           // Copy constructor
        AMateria& operator=(const AMateria& other); // Copy assignment
        virtual ~AMateria();  

        // Custom constructor
        AMateria(std::string const & type);

        std::string const & getType() const; //Returns the materia type
        virtual AMateria* clone() const = 0;
        virtual void use(ICharacter& target);
};

#endif