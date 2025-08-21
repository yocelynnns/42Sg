/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:36:06 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/08/14 14:36:00 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try {
        BitcoinExchange btcDB("data.csv");

        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            std::cerr << "Error: could not open file." << std::endl;
            return 1;
        }

        std::string line;
        bool firstLine = true;
        while (std::getline(input, line))
        {
            if (firstLine)
            {
                firstLine = false;
                if (line == "date | value")
                    continue;
            }
            if (line.empty())
                continue;

            size_t pipe = line.find('|');
            if (pipe == std::string::npos)
            {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }

            std::string date = BitcoinExchange::trim(line.substr(0, pipe));
            std::string value = BitcoinExchange::trim(line.substr(pipe + 1));

            try {
                BitcoinExchange::isValidDate(date);
                BitcoinExchange::isValidVal(value);

                float rate = btcDB.getRate(date);
                float val;
                std::stringstream ss(value);
                ss >> val;

                std::cout << date << " => " << value << " = " << (val * rate) << std::endl;
            } 
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } 
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
