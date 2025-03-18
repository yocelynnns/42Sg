/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:37:03 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/18 16:46:40 by yocelynnns       ###   ########.fr       */
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

public:
    PhoneBook();

    void AddContact();
    void SearchContact() const;
};

#endif
