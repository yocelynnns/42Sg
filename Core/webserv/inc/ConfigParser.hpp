/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:12:09 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/09/03 15:16:43 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <map>
#include <stack>

class ConfigParser
{
private:
    std::string _filename;
    std::vector<std::string> includes;

    struct LocationBlock {
        std::string path;
        std::vector<std::string> methods;
        std::string root;
        bool autoindex;
        std::vector<std::string> index_files;
        std::string upload_store;
        std::string cgi_pass;
        std::map<std::string, std::string> extra_directives;

        LocationBlock() : autoindex(false) {}
    };

    struct ServerBlock {
        std::vector<int> listen_ports;
        bool ssl_enabled;
        std::vector<std::string> server_names;
        std::string root;
        std::vector<std::string> index_files;
        std::map<std::string, std::string> extra_directives;
        std::vector<LocationBlock> locations;

        ServerBlock() : ssl_enabled(false) {}
    };

    std::vector<ServerBlock> servers;

public:
    ConfigParser(const std::string &filename);
    void parse();

    const std::vector<std::string>& getIncludes() const;
    const std::vector<ServerBlock>& getServers() const;
};

#endif
