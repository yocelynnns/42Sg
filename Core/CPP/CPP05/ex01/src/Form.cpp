/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:44:41 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/27 14:49:39 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form()
 : name("Default"), isSigned(true), signGrade(1), execGrade(1)
{
    std::cout << "Form " << name << " is created (default)." << std::endl;
}

Form::Form(const Form& other)
 : name(other.name), isSigned(other.isSigned), signGrade(other.signGrade), execGrade(other.execGrade)
{
    std::cout << "Form " << name << " is copied." << std::endl;
}

Form& Form::operator=(const Form& other)
{
    if (this != &other)
        isSigned = other.isSigned;
    std::cout << "Form " << name << " is assigned." << std::endl;
    return *this;
}

Form::~Form() {
    std::cout << "Form " << name << " is destroyed." << std::endl;
}

Form::Form(const std::string& name, int signGrade, int execGrade)
 : name(name), isSigned(false), signGrade(signGrade), execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw GradeTooLowException();
        
    std::cout << "Form " << name << " is created." << std::endl;
}

const std::string& Form::getName() const {
    return name;
}

bool Form::getIsSigned() const {
    return isSigned;
}

int Form::getSignGrade() const {
    return signGrade;
}

int Form::getExecGrade() const {
    return execGrade;
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Form: Grade too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form: Grade too low!";
}

void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > signGrade)
        throw GradeTooLowException();
    isSigned = true;
}

std::ostream& operator<<(std::ostream& os, const Form& f)
{
    os << "Form \"" << f.getName() << "\", signed: ";
    if (f.getIsSigned()) {
        os << "yes";
    } else {
        os << "no";
    }
    os << ", sign grade: " << f.getSignGrade()
       << ", exec grade: " << f.getExecGrade();
    return os;
}
