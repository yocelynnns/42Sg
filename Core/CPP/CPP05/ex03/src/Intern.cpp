/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:18:05 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/30 14:38:05 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

// Default constructor
Intern::Intern()
{
    std::cout << "Intern is created (default)." << std::endl;
}

// Copy constructor
Intern::Intern(const Intern& other)
{
    (void)other;
    std::cout << "Intern is copied." << std::endl;
}

// Copy assignment operator
Intern& Intern::operator=(const Intern& other)
{
    (void)other;
    std::cout << "Intern is assigned." << std::endl;
    return *this;
}

// Destructor
Intern::~Intern() {
    std::cout << "Intern is destroyed." << std::endl;
}

typedef AForm* (*FormCreator)(const std::string& target);

// Helper functions
static AForm* createShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}

static AForm* createPardon(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    const std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    FormCreator creators[] = {
        &createShrubbery,
        &createRobotomy,
        &createPardon
    };

    for (int i = 0; i < 3; ++i) {
        if (formName == formNames[i]) {
            std::cout << "Intern creates " << formName << std::endl;
            return creators[i](target);
        }
    }

    std::cerr << "Error: Form \"" << formName << "\" does not exist." << std::endl;
    return NULL;
}
