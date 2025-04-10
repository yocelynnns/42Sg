/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:16:05 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 00:49:40 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
public:
    // Orthodox Canonical Form
    WrongCat();                                // Default constructor
    WrongCat(const WrongCat& other);           // Copy constructor
    WrongCat& operator=(const WrongCat& other); // Copy assignment
    ~WrongCat(); 
      
    void makeSound() const;
};

#endif
