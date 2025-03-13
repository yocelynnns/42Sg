/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:04:23 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/13 14:37:01 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main() {
    PhoneBook phoneBook;
    std::string command;

    while (1) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        getline(std::cin, command);

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
