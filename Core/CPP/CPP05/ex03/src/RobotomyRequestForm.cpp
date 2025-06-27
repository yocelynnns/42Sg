/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:07:48 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/27 21:17:26 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

// Default constructor
RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 45), target("Default")
{
    std::cout << "RobotomyRequestForm " << target << " is created (default)." << std::endl;
}

// Custom constructor
RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", 72, 45), target(target)
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
