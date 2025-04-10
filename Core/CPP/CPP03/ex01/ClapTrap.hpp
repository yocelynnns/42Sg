/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:45:46 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/10 14:30:14 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap
{
    protected:
        std::string name;
        int hitPts;
        int energyPts;
        int attackDmg;
        int maxHitPts;
    public:
        // Orthodox Canonical Form
        ClapTrap();                                // Default constructor
        ClapTrap(const ClapTrap& other);           // Copy constructor
        ClapTrap& operator=(const ClapTrap& other); // Copy assignment
        ~ClapTrap();                               // Destructor

        // Custom constructor
        ClapTrap(std::string name);

        // Member functions
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif