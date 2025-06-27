/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:07:48 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/30 14:28:43 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

// Default constructor
RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 48), target("Default")
{
    std::cout << "RobotomyRequestForm " << target << " is created (default)." << std::endl;
}

// Custom constructor
RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", 72, 48), target(target)
{
    std::srand(std::time(NULL));
    std::cout << "RobotomyRequestForm " << target << " is created." << std::endl;
}

// Copy constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other), target(other.target)
{
    std::cout << "RobotomyRequestForm " << target << " is copied." << std::endl;
}

// Copy assignment operator
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
    // name is const so cant be assigned
    if (this != &other)
        target = other.target;
    std::cout << "RobotomyRequestForm " << target << " is assigned." << std::endl;
    return *this;
}

// Destructor
RobotomyRequestForm::~RobotomyRequestForm() {
    std::cout << "RobotomyRequestForm " << target << " is destroyed." << std::endl;
}

void RobotomyRequestForm::executeAction() const {
    std::cout << "Bzzzz... drilling noises..." << std::endl;
    if (std::rand() % 2)
        std::cout << target << " has been robotomized successfully." << std::endl;
    else
        std::cout << "Robotomy failed on " << target << "." << std::endl;
}
