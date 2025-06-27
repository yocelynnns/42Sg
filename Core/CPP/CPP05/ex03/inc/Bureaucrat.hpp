/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:56:18 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/06/27 21:02:47 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include "AForm.hpp"

class AForm;

class Bureaucrat {
    private:
        const std::string name;
        int grade;
    public:
        // Orthodox Canonical Form
        Bureaucrat();                                // Default constructor
        Bureaucrat(const Bureaucrat& other);           // Copy constructor
        Bureaucrat& operator=(const Bureaucrat& other); // Copy assignment
        ~Bureaucrat();                               // Destructor
        
        // Custom constructor
        Bureaucrat(const std::string& name, int grade);

        // Member functions 
        const std::string& getName() const;
        int getGrade() const;
        
        void incGrade();
        void decGrade();

        void signForm(AForm& form);
        void executeForm(const AForm& form) const;

        class GradeTooHighException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
        
        class GradeTooLowException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif
