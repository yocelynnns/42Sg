/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:37:09 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/15 21:08:36 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : contactIndex(0), contactCount(0) {}

bool PhoneBook::IsValidPhoneNumber(const std::string &phoneNumber) const {
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
    if (!getline(std::cin, firstName))
        exit(1);
    while (firstName.empty()) {
        std::cout << "First Name cannot be empty. Please enter again: ";
        if (!getline(std::cin, firstName))
            exit(1);
    }
    
    std::cout << "Enter Last Name: ";
    if (!getline(std::cin, lastName))
        exit(1);
    while (lastName.empty()) {
        std::cout << "Last Name cannot be empty. Please enter again: ";
        if (!getline(std::cin, lastName))
            exit(1);
    }
    
    std::cout << "Enter Nick Name: ";
    if (!getline(std::cin, nickName))
        exit(1);
    while (nickName.empty()) {
        std::cout << "Nick Name cannot be empty. Please enter again: ";
        if (!getline(std::cin, nickName))
            exit(1);
    }
        
    std::cout << "Enter Phone Number (digits only): ";
    if (!getline(std::cin, phoneNumber))
        exit(1);
    while (phoneNumber.empty() || !IsValidPhoneNumber(phoneNumber)) {
        std::cout << "Invalid phone number! Please enter only digits: ";
        if (!getline(std::cin, phoneNumber))
            exit(1);
    }
    
    std::cout << "Enter Darkest Secret: ";
    if (!getline(std::cin, darkestSecret))
        exit(1);
    while (darkestSecret.empty()) {
        std::cout << "Darkest Secret cannot be empty. Please enter again: ";
        if (!getline(std::cin, darkestSecret))
            exit(1);
    }

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
    if (!getline(std::cin, input))
        exit(1);
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
