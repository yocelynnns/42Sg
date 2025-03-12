/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:04:23 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/12 17:42:29 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

int main() {
    PhoneBook phoneBook;
    string command;

    while (1) {
        cout << "Enter command (ADD, SEARCH, EXIT): ";
        getline(cin, command);

        if (command == "ADD") {
            phoneBook.AddContact();
        } 
        else if (command == "SEARCH") {
            phoneBook.SearchContact();
        } 
        else if (command == "EXIT") {
            cout << "Exiting phonebook...\n";
            break;
        } 
        else {
            cout << "Invalid command. Use ADD, SEARCH, or EXIT.\n";
        }
    }

    return 0;
}