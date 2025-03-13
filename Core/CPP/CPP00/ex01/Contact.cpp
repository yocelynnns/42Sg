/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:36:19 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/13 20:45:37 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

Contact::Contact(std::string firstName, std::string lastName, std::string nickName, std::string phoneNumber, std::string darkestSecret)
    : FirstName(firstName), LastName(lastName), NickName(nickName), PhoneNumber(phoneNumber), DarkestSecret(darkestSecret) {}

void Contact::DisplayInfo() const {
    std::cout << "First Name: " << FirstName << std::endl;
    std::cout << "Last Name: " << LastName << std::endl;
    std::cout << "Nick Name: " << NickName << std::endl;
    std::cout << "Phone Number: " << PhoneNumber << std::endl;
    std::cout << "Darkest Secret: " << DarkestSecret << std::endl;
}

void Contact::DisplaySummary(int index) const {
    std::cout << std::setw(10) << index << "|";

    if (FirstName.length() > 9) {
        std::cout << FirstName.substr(0, 9) << ".|";
    } else {
        std::cout << std::setw(10) << FirstName << "|";
    }

    if (LastName.length() > 9) {
        std::cout << LastName.substr(0, 9) << ".|";
    } else {
        std::cout << std::setw(10) << LastName << "|";
    }

    if (NickName.length() > 9) {
        std::cout << NickName.substr(0, 9) << ".|";
    } else {
        std::cout << std::setw(10) << NickName << "|";
    }

    std::cout << std::endl;
}
