/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:35:31 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/08/11 15:07:03 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <ctime>
#include <string>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>
#include <map>

class BitcoinExchange {
private:
    std::map<std::string, float> coinRate;

public:
    BitcoinExchange();
    BitcoinExchange(const std::string& filename);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
    
    float getRate(const std::string& date) const;

    static bool isAllDigits(const std::string& s);
    static bool isValidDate(const std::string& date);
    static bool isValidVal(const std::string& value);
    static std::string trim(const std::string& str);

    class DateException : public std::exception {
    private:
        std::string _msg;
    public:
        DateException(const std::string& msg) : _msg(msg) {}
        virtual ~DateException() throw() {}
        virtual const char* what() const throw() { return _msg.c_str(); }
    };

    class ValueException : public std::exception {
    private:
        std::string _msg;
    public:
        ValueException(const std::string& msg) : _msg(msg) {}
        virtual ~ValueException() throw() {}
        virtual const char* what() const throw() { return _msg.c_str(); }
    };  
};

#endif
