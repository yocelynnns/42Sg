/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:20:37 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:19:07 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Brain.hpp"

Brain::Brain() {
    std::cout << "Brain Constructor called" << std::endl;
}

Brain::~Brain() {
    std::cout << "Brain Destructor called" << std::endl;
}

// Copy constructor
Brain::Brain(const Brain& other)
{
    std::cout << "Brain Copy Constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
            ideas[i] = other.ideas[i];
}

// Copy assignment operator
Brain& Brain::operator=(const Brain& other)
{
    std::cout << "Brain Copy Assignment called" << std::endl;
    if (this != &other)
    {
        for (int i = 0; i < 100; i++)
            ideas[i] = other.ideas[i];
    }
    return *this;
}