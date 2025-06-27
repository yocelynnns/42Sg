/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:10:59 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 17:25:08 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

// Default constructor
PresidentialPardonForm::PresidentialPardonForm()
    : AForm("PresidentialPardonForm", 25, 5), target("Default")
{
    std::cout << "PresidentialPardonForm " << target << " is created (default)." << std::endl;
}

// Custom constructor
PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("PresidentialPardonForm", 25, 5), target(target)
{
    std::cout << "PresidentialPardonForm " << target << " is created." << std::endl;
}

// Copy constructor
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other)
    : AForm(other), target(other.target)
{
    std::cout << "PresidentialPardonForm " << target << " is copied." << std::endl;
}

// Copy assignment operator
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
    // name is const so cant be assigned
    if (this != &other)
        target = other.target;
    std::cout << "PresidentialPardonForm " << target << " is assigned." << std::endl;
    return *this;
}

// Destructor
PresidentialPardonForm::~PresidentialPardonForm() {
    std::cout << "PresidentialPardonForm " << target << " is destroyed." << std::endl;
}

void PresidentialPardonForm::executeAction() const {
    std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
