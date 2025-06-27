/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:01:27 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 17:22:26 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

// Default constructor
ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), target("Default") {
    std::cout << "ShrubberyCreationForm " << target << " is created (default)." << std::endl;
}

// Custom constructor
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), target(target) {
    std::cout << "ShrubberyCreationForm " << target << " is created." << std::endl;
}

// ✅ Fix: Add AForm initialization
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other), target(other.target) {
    std::cout << "ShrubberyCreationForm " << target << " is copied." << std::endl;
}

// Assignment operator
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other)
        target = other.target;
    std::cout << "ShrubberyCreationForm " << target << " is assigned." << std::endl;
    return *this;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm() {
    std::cout << "ShrubberyCreationForm " << target << " is destroyed." << std::endl;
}

// ✅ Fix: use .c_str()
void ShrubberyCreationForm::executeAction() const {
    std::ofstream ofs((target + "_shrubbery").c_str());
    if (!ofs)
        return;

    ofs << "       _-_\n"
           "    /~~   ~~\\\n"
           " /~~         ~~\\\n"
           "{               }\n"
           " \\  _-     -_  /\n"
           "   ~  \\\\ //  ~\n"
           "_- -   | | _- _\n"
           "  _ -  | |   -_\n"
           "      // \\\\\n";
    ofs.close();
}
