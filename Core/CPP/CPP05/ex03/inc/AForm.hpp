/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:57:44 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/27 21:02:44 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
    private:
        const std::string name;
        bool isSigned;
        const int signGrade;
        const int execGrade;
    public:
        // Orthodox Canonical Form
        AForm();                                // Default constructor
        AForm(const AForm& other);           // Copy constructor
        AForm& operator=(const AForm& other); // Copy assignment
        virtual ~AForm();                               // Destructor

        AForm(const std::string& name, int gradeSign, int gradeExec);
        
        // Getters
        const std::string& getName() const;
        bool getIsSigned() const;
        int getSignGrade() const;
        int getExecGrade() const;

         // Member function
        void beSigned(const Bureaucrat& b);
        void execute(const Bureaucrat& executor) const;

        virtual void executeAction() const = 0;

        // Exceptions
        class GradeTooHighException : public std::exception {
        public:
            const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {
        public:
            const char* what() const throw();
        };
        
        class FormNotSignedException : public std::exception {
        public:
            const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif
