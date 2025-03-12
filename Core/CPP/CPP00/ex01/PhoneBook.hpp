/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:35:50 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/12 17:38:48 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook {
    private:
        Contact contacts[8];
        int contactIndex;
        int contactCount;
    
    public:
        PhoneBook() : contactIndex(0), contactCount(0) {}
    
        void AddContact() {
            string firstName, lastName, nickName, phoneNumber, darkestSecret;
    
            cout << "Enter First Name: ";
            getline(cin, firstName);
            cout << "Enter Last Name: ";
            getline(cin, lastName);
            cout << "Enter Nick Name: ";
            getline(cin, nickName);
            cout << "Enter Phone Number: ";
            getline(cin, phoneNumber);
            cout << "Enter Darkest Secret: ";
            getline(cin, darkestSecret);
    
            contacts[contactIndex] = Contact(firstName, lastName, nickName, phoneNumber, darkestSecret);
            contactIndex = (contactIndex + 1) % 8;
            if (contactCount < 8)
                contactCount++;
    
            cout << "Contact added successfully!\n\n";
        }
    
        void SearchContact() {
            if (contactCount == 0) {
                cout << "No contacts to search.\n";
                return;
            }
            for (int i = 0; i < contactCount; i++) {
                contacts[i].DisplaySummary(i + 1);
            }
    
            cout << "Enter contact index: ";
            string input;
            getline(cin, input);
            int index = stoi(input);
    
            if (index >= 1 && index <= contactCount) {
                contacts[index - 1].DisplayInfo();
            } else {
                cout << "Invalid index. Please enter a valid contact number.\n";
            }
        }
    };