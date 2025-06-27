/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:56 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 15:10:21 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
    private:
        const std::string name;
        bool isSigned;
        const int signGrade;
        const int execGrade;
    public:
        // Orthodox Canonical Form
        Form();                                // Default constructor
        Form(const Form& other);           // Copy constructor
        Form& operator=(const Form& other); // Copy assignment
        ~Form();                               // Destructor

        Form(const std::string& name, int gradeSign, int gradeExec);
        
        // Getters
        const std::string& getName() const;
        bool getIsSigned() const;
        int getSignGrade() const;
        int getExecGrade() const;

         // Member function
        void beSigned(const Bureaucrat& b);

        // Exceptions
        class GradeTooHighException : public std::exception {
        public:
            const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {
        public:
            const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif
