/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:36:52 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/12 17:42:04 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

class Contact
{
    private:
        std::string FirstName;
        std::string LastName;
        std::string NickName;
        std::string PhoneNumber;
        std::string DarkestSecret;
    
    public:
        Contact(string firstName, string lastName, string nickName, string phoneNumber, string darkestSecret) {
            this->FirstName = firstName;
            this->LastName = lastName;
            this->NickName = nickName;
            this->PhoneNumber = phoneNumber;
            this->DarkestSecret = darkestSecret;
        }
    
        Contact() {}
    
        void DisplayInfo() {
            std::cout << "First Name: " << FirstName << std::endl;
            std::cout << "Last Name: " << LastName << std::endl;
            std::cout << "Nick Name: " << NickName << std::endl;
            std::cout << "Phone Number: " << PhoneNumber << std::endl;
            std::cout << "Darkest Secret: " << DarkestSecret << std::endl;
        }
    
        void DisplaySummary(int index) const {
            cout << std::setw(10) << index << "|";
            
            if (FirstName.length() > 9) {
                cout << FirstName.substr(0, 9) << ".|";
            } else {
                cout << std::setw(10) << FirstName << "|";
            }
    
            if (LastName.length() > 9) {
                cout << LastName.substr(0, 9) << ".|";
            } else {
                cout << std::setw(10) << LastName << "|";
            }
    
            if (NickName.length() > 9) {
                cout << NickName.substr(0, 9) << ".|";
            } else {
                cout << std::setw(10) << NickName << "|";
            }
    
            cout << std::endl;
        }
    
        bool isEmpty() {
            return FirstName.empty();
        }
};
