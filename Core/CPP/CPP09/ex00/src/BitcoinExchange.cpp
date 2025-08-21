/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:36:03 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/08/14 14:34:09 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine)
        {
            firstLine = false;
            continue;
        }
        if (line.empty())
            continue;

        size_t comma = line.find(',');
        if (comma == std::string::npos)
            continue;

        std::string date = trim(line.substr(0, comma));
        std::string rateStr = trim(line.substr(comma + 1));

        try {
            isValidDate(date);
        } catch (...) {
            continue;
        }

        float rate;
        std::stringstream ss(rateStr);
        if (!(ss >> rate))
            continue;

        coinRate[date] = rate;
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : coinRate(other.coinRate) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other)
        coinRate = other.coinRate;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

float BitcoinExchange::getRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = coinRate.find(date);
    if (it != coinRate.end())
        return it->second;

    it = coinRate.lower_bound(date);
    if (it == coinRate.begin())
        throw DateException("Error: no earlier date in DB => " + date);

    --it;
    return it->second;
}

bool BitcoinExchange::isAllDigits(const std::string& s) {
    for (size_t i = 0; i < s.length(); ++i)
        if (!std::isdigit(s[i]))
            return false;
    return true;
}

bool BitcoinExchange::isValidVal(const std::string &value) {
    float val;
    std::stringstream val_ss(value);
    if (!(val_ss >> val) || !val_ss.eof())  
        throw ValueException("Error: not a valid value => " + value);
    if (val < 0)
        throw ValueException("Error: not a positive number => " + value);
    else if (val > 1000)
        throw ValueException("Error: too large a number => " + value);
    return true;
}

bool BitcoinExchange::isValidDate(const std::string &date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        throw DateException("Error: bad input => " + date);

    std::string y_str = date.substr(0, 4);
    std::string m_str = date.substr(5, 2);
    std::string d_str = date.substr(8, 2);

    if (!isAllDigits(y_str) || !isAllDigits(m_str) || !isAllDigits(d_str))
        throw DateException("Error: bad input => " + date);

    int y = atoi(y_str.c_str());
    int m = atoi(m_str.c_str());
    int d = atoi(d_str.c_str());

    if (m < 1 || m > 12)
        throw DateException("Error: bad input => " + date);

    int max_day;
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            max_day = 31;
            break;
        case 4: case 6: case 9: case 11:
            max_day = 30;
            break;
        case 2:
            if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
                max_day = 29;
            else
                max_day = 28;
            break;
    }

    if (d < 1 || d > max_day)
        throw DateException("Error: bad input => " + date);

    time_t t = time(NULL);
    tm *now = localtime(&t);
    char today[11];
    std::strftime(today, sizeof(today), "%Y-%m-%d", now);
    if (date > std::string(today))
        throw DateException("Error: bad input => " + date);

    return true;
}

std::string BitcoinExchange::trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    if (start == std::string::npos)
        return "";
    return str.substr(start, end - start + 1);
}
