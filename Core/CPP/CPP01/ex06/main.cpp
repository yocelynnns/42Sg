/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:45:17 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/19 16:01:37 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char **argv)
{
    Harl harl;

    if (argc != 2) {
        std::cout << "Error! ";
        std::cout << "Usage: ./harlFilter <complaint_level>" << std::endl;
        return 1;
    }
    harl.complain(argv[1]);

    return 0;
}