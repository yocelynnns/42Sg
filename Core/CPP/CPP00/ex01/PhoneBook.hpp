/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:37:03 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/15 21:13:34 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <sstream>

class PhoneBook {
private:
    Contact contacts[8];
    int contactIndex;
    int contactCount;

    bool IsValidPhoneNumber(const std::string &phoneNumber) const;
    std::string GetValidInput(const std::string& prompt);
    std::string GetValidPhoneNumber();

public:
    PhoneBook();

    void AddContact();
    void SearchContact() const;
};

#endif
