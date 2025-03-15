/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:04:23 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/15 21:03:33 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main() {
    PhoneBook phoneBook;
    std::string command;

    while (1) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!getline(std::cin, command))
            return (1);
        if (command == "ADD") {
            phoneBook.AddContact();
        } 
        else if (command == "SEARCH") {
            phoneBook.SearchContact();
        } 
        else if (command == "EXIT") {
            std::cout << "Exiting phonebook...\n";
            break;
        } 
        else {
            std::cout << "Invalid command. Use ADD, SEARCH, or EXIT.\n";
        }
    }

    return 0;
}
