/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:08:42 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/19 03:06:18 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main(int argc, char **argv)
{
    if (argc == 4)
    {
        std::ifstream src(argv[1]);
        std::string s1 = argv[2];
        std::string s2 = argv[3];
        std::string filename = std::string(argv[1]) + ".replace";
        std::ofstream dst(filename.c_str());

        if (!src.is_open() || !dst.is_open())
        {
            std::cerr << "Error: Could not open files.\n";
            return 1;
        }
        std::string content;
        while (std::getline(src, content))
        {
            size_t i = 0;
            while ((i = content.find(s1, i)) != std::string::npos) {  // Find s1 in text
                content = content.substr(0, i) + s2 + content.substr(i + s1.length());  // Replace manually
                i += s2.length();  // Move past the replaced part to continue
            }
            dst << content << std::endl;
        }
        src.close();
        dst.close();
        return (0);   
    }
    else
    {
        std::cout << "Error!" << std::endl;
        std::cout << "Usage: ./sed filename s1 s2" << std::endl;
        return (1);
    }
}