/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:16:11 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 16:19:57 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal {
    protected:
        std::string type;
    public:
        // Orthodox Canonical Form
        WrongAnimal();                                // Default constructor
        WrongAnimal(const WrongAnimal& other);           // Copy constructor
        WrongAnimal& operator=(const WrongAnimal& other); // Copy assignment
        ~WrongAnimal();
        
        void makeSound() const;
        std::string getType() const;
};

#endif
