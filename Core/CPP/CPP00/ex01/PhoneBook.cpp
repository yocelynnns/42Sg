/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:37:09 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/13 20:46:43 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : contactIndex(0), contactCount(0) {}

bool PhoneBook::IsValidPhoneNumber(const std::string& phoneNumber) const {
    for (size_t i = 0; i < phoneNumber.length(); i++) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }
    return !phoneNumber.empty();
}

void PhoneBook::AddContact() {
    std::string firstName, lastName, nickName, phoneNumber, darkestSecret;

    std::cout << "Enter First Name: ";
    getline(std::cin, firstName);
    std::cout << "Enter Last Name: ";
    getline(std::cin, lastName);
    std::cout << "Enter Nick Name: ";
    getline(std::cin, nickName);
    std::cout << "Enter Phone Number (digits only): ";
    getline(std::cin, phoneNumber);
    
    while (!IsValidPhoneNumber(phoneNumber)) {
        std::cout << "Invalid phone number! Please enter only digits: ";
        getline(std::cin, phoneNumber);
    }
    
    std::cout << "Enter Darkest Secret: ";
    getline(std::cin, darkestSecret);

    contacts[contactIndex] = Contact(firstName, lastName, nickName, phoneNumber, darkestSecret);
    contactIndex = (contactIndex + 1) % 8;
    if (contactCount < 8) {
        contactCount++;
    }

    std::cout << "Contact added successfully!\n\n";
}

void PhoneBook::SearchContact() const {
    if (contactCount == 0) {
        std::cout << "No contacts to search.\n";
        return;
    }
    
    for (int i = 0; i < contactCount; i++) {
        contacts[i].DisplaySummary(i + 1);
    }

    std::cout << "Enter contact index: ";
    std::string input;
    getline(std::cin, input);
    std::stringstream ss(input);
    int index;
    
    if (!(ss >> index)) {
        std::cout << "Invalid input. Please enter a valid number.\n";
        return;
    }

    if (index >= 1 && index <= contactCount) {
        contacts[index - 1].DisplayInfo();
    } else {
        std::cout << "Invalid index. Please enter a valid contact number.\n";
    }
}
