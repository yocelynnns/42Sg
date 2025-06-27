/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:54:12 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 16:54:32 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm()
 : name("Default"), isSigned(true), signGrade(1), execGrade(1)
{
    std::cout << "AForm " << name << " is created (default)." << std::endl;
}

AForm::AForm(const AForm& other)
 : name(other.name), isSigned(other.isSigned), signGrade(other.signGrade), execGrade(other.execGrade)
{
    std::cout << "AForm " << name << " is copied." << std::endl;
}

AForm& AForm::operator=(const AForm& other)
{
    if (this != &other)
        isSigned = other.isSigned;
    std::cout << "AForm " << name << " is assigned." << std::endl;
    return *this;
}

AForm::~AForm() {
    std::cout << "AForm " << name << " is destroyed." << std::endl;
}

AForm::AForm(const std::string& name, int signGrade, int execGrade)
 : name(name), isSigned(false), signGrade(signGrade), execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw GradeTooLowException();
        
    std::cout << "AForm " << name << " is created." << std::endl;
}

const std::string& AForm::getName() const {
    return name;
}

bool AForm::getIsSigned() const {
    return isSigned;
}

int AForm::getSignGrade() const {
    return signGrade;
}

int AForm::getExecGrade() const {
    return execGrade;
}

const char* AForm::GradeTooHighException::what() const throw() {
    return "AForm: Grade too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "AForm: Grade too low!";
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "AForm: Form not signed!";
}

void AForm::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > signGrade)
        throw GradeTooLowException();
    isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const {
    if (!isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > execGrade)
        throw GradeTooLowException();
    executeAction();
}

std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "AForm \"" << f.getName()
       << "\", signed: " << (f.getIsSigned() ? "yes" : "no")
       << ", sign grade: " << f.getSignGrade()
       << ", exec grade: " << f.getExecGrade();
    return os;
}
