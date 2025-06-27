/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:06:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 17:07:31 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm {
    private:
        std::string target;

    public:
        // Orthodox Canonical Form
        RobotomyRequestForm();                                // Default constructor
        RobotomyRequestForm(const RobotomyRequestForm& other);           // Copy constructor
        RobotomyRequestForm& operator=(const RobotomyRequestForm& other); // Copy assignment
        ~RobotomyRequestForm();                               // Destructor
       
        RobotomyRequestForm(const std::string& target);
       
        void executeAction() const;
};

#endif
