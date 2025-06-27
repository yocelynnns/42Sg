/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:09:57 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 17:10:46 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
    private:
        std::string target;

    public:
        // Orthodox Canonical Form
        PresidentialPardonForm();                                // Default constructor
        PresidentialPardonForm(const PresidentialPardonForm& other);           // Copy constructor
        PresidentialPardonForm& operator=(const PresidentialPardonForm& other); // Copy assignment
        ~PresidentialPardonForm();                               // Destructor    

        PresidentialPardonForm(const std::string& target);

        void executeAction() const;
};

#endif
