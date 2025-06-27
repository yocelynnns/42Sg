/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:00:15 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/28 16:58:33 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

const std::string& Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

void Bureaucrat::incGrade() {
    if (grade <= 1)
        throw GradeTooHighException();
    grade--;
}

void Bureaucrat::decGrade() {
    if (grade >= 150)
        throw GradeTooLowException();
    grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Bureaucrat: Grade too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Bureaucrat: Grade too low!";
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

void Bureaucrat::signForm(AForm& form)
{
    try {
        form.beSigned(*this);
        std::cout << name << " signed " << form.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cout << name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::executeForm(const AForm& form) const {
    try {
        form.execute(*this);
        std::cout << name << " executes " << form.getName() << std::endl;
    } catch (std::exception& e) {
        std::cout << name << " cannot execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
