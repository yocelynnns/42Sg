/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:59:35 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 17:01:02 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm {
    private:
        std::string target;

    public:
        // Orthodox Canonical Form
        ShrubberyCreationForm();                                // Default constructor
        ShrubberyCreationForm(const ShrubberyCreationForm& other);           // Copy constructor
        ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other); // Copy assignment
        ~ShrubberyCreationForm();                               // Destructor

        ShrubberyCreationForm(const std::string& target);
        
        void executeAction() const;
};

#endif
