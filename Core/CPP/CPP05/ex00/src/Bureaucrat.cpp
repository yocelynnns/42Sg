/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:00:15 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/27 21:06:44 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

const std::string& Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

void Bureaucrat::decGrade()
{
    if (grade <= 1)
        throw GradeTooLowException();
    grade--;
}

void Bureaucrat::incGrade()
{
    if (grade >= 150)
        throw GradeTooHighException();
    grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low!";
}


std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return os;
}

// Default constructor
Bureaucrat::Bureaucrat()
    : name("Default"), grade(150)
{
    std::cout << "Bureaucrat " << name << " is created (default)." << std::endl;
}

// Custom constructor
Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name(name), grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

// Copy constructor
Bureaucrat::Bureaucrat(const Bureaucrat& other)
    : name(other.name), grade(other.grade)
{
    std::cout << "Bureaucrat " << name << " is copied." << std::endl;
}

// Copy assignment operator
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
    // name is const so cant be assigned
    if (this != &other)
        grade = other.grade;
    std::cout << "Bureaucrat " << name << " is assigned." << std::endl;
    return *this;
}

// Destructor
Bureaucrat::~Bureaucrat() {
    std::cout << "Bureaucrat " << name << " is destroyed." << std::endl;
}