/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:10:58 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/09/02 16:47:02 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ConfigParser.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    try {
        ConfigParser parser(argv[1]);
        parser.parse();

        // You’ll later get config object and pass it to Server
        // Server server(parser.getConfig());
        // server.run();

    } catch (const std::exception &e) {
        std::cerr << "!!!! " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
