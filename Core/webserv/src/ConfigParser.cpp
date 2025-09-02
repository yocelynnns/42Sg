/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:18:52 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/09/02 21:12:10 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(const std::string &filename) {
    _filename = filename;
}

const std::vector<std::string>& ConfigParser::getIncludes() const {
    return includes;
}

const std::vector<ConfigParser::ServerBlock>& ConfigParser::getServers() const {
    return servers;
}

void ConfigParser::validateServer(const ServerBlock &server, int line_number) const
{
    for (size_t i = 0; i < server.listen_ports.size(); ++i)
    {
        int port = server.listen_ports[i];
        if (port < 1 || port > 65535)
        {
            std::ostringstream oss;
            oss << line_number;
            std::ostringstream port_stream;
            port_stream << port;
            throw std::runtime_error("Error at line " + oss.str() + ": invalid port " + port_stream.str());
        }
    }
    if (server.index_files.empty() && server.extra_directives.find("return") == server.extra_directives.end()) {
        std::ostringstream oss;
        oss << line_number;
        throw std::runtime_error("Error at line " + oss.str() + ": index files cannot be empty");
    }

    if (server.server_names.empty())
    {
        std::ostringstream oss; oss << line_number;
        throw std::runtime_error("Error at line " + oss.str() + ": server_name cannot be empty");
    }
    if (server.index_files.empty())
    {
        std::ostringstream oss; oss << line_number;
        throw std::runtime_error("Error at line " + oss.str() + ": index files cannot be empty");
    }
}

void ConfigParser::parse()
{
    std::ifstream file(_filename.c_str());
    if (!file.is_open())
        throw std::runtime_error(std::string("Cannot open config file: ") + _filename);

    if (_filename.size() < 5 || _filename.substr(_filename.size() - 5) != ".conf")
        throw std::runtime_error("Error: invalid config file extension (expected .conf)");

    if (file.peek() == std::ifstream::traits_type::eof())
        throw std::runtime_error("Error: config file is empty");

    std::string line;
    int line_number = 0;
    std::stack<std::string> block_stack;
    ServerBlock* current_server = NULL;
    LocationBlock* current_location = NULL;

    while (std::getline(file, line))
    {
        line_number++;

        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos)
            continue;
        size_t end = line.find_last_not_of(" \t");
        line = line.substr(start, end - start + 1);

        if (line[0] == '#')
            continue;

        if (line == "}")
        {
            if (block_stack.empty())
            {
                std::ostringstream oss; oss << line_number;
                throw std::runtime_error("Error at line " + oss.str() + ": unexpected '}'");
            }
            std::string top_block = block_stack.top();
            block_stack.pop();

            if (top_block == "server")
            {
                validateServer(*current_server, line_number);
                current_server = NULL;
            }
            else if (top_block.find("location") == 0)
                current_location = NULL;
            continue;
        }

        size_t brace_pos = line.find('{');
        if (brace_pos != std::string::npos)
        {
            std::string block_name = line.substr(0, brace_pos);
            block_name.erase(block_name.find_last_not_of(" \t") + 1);

            if (block_name == "server")
            {
                servers.push_back(ServerBlock());
                current_server = &servers.back();
            }
            else if (block_name.find("location") == 0)
            {
                if (!current_server)
                {
                    std::ostringstream oss_line;
                    oss_line << line_number;
                    throw std::runtime_error("Location block outside of server at line " + oss_line.str());
                }

                current_server->locations.push_back(LocationBlock());
                current_location = &current_server->locations.back();

                size_t path_start = block_name.find(" ") + 1;
                if (path_start != std::string::npos)
                    current_location->path = block_name.substr(path_start);
            }

            block_stack.push(block_name);

            size_t close_brace = line.find('}', brace_pos);
            if (close_brace != std::string::npos)
            {
                block_stack.pop();
                if (block_name == "server")
                    current_server = NULL;
                if (block_name.find("location") == 0)
                    current_location = NULL;
            }
            continue;
        }

        size_t semicolon_pos = line.find(';');
        if (semicolon_pos == std::string::npos)
        {
            std::ostringstream oss; oss << line_number;
            throw std::runtime_error("Error at line " + oss.str() + ": missing semicolon ';'");
        }

        std::string directive_line = line.substr(0, semicolon_pos);

        size_t key_end = directive_line.find_first_of(" \t");
        if (key_end == std::string::npos)
        {
            std::ostringstream oss; oss << line_number;
            throw std::runtime_error("Error at line " + oss.str() + ": invalid directive format");
        }

        std::string key = directive_line.substr(0, key_end);
        std::string value = directive_line.substr(key_end);
        size_t val_start = value.find_first_not_of(" \t");
        size_t val_end = value.find_last_not_of(" \t");
        if (val_start != std::string::npos)
            value = value.substr(val_start, val_end - val_start + 1);
        else
            value = "";

        if (current_location)
        {
            if (key == "root")
                current_location->root = value;
            else if (key == "index")
            {
                std::istringstream iss(value); std::string f;
                while (iss >> f)
                    current_location->index_files.push_back(f);
            }
            else if (key == "autoindex")
                current_location->autoindex = (value == "on");
            else if (key == "methods")
            {
                std::istringstream iss(value); std::string m;
                while (iss >> m)
                    current_location->methods.push_back(m);
            }
            else if (key == "upload_store")
                current_location->upload_store = value;
            else if (key == "cgi_pass")
                current_location->cgi_pass = value;
            else
                current_location->extra_directives[key] = value;
        }
        else if (current_server)
        {
            if (key == "listen")
            {
                std::istringstream iss(value);
                int port;
                std::string flag;
                
                iss >> port;
                current_server->listen_ports.push_back(port);
                while (iss >> flag)
                {
                    if (flag == "ssl")
                        current_server->ssl_enabled = true;
                }
            }
            else if (key == "server_name")
            {
                std::istringstream iss(value);
                std::string name;
                while (iss >> name)
                    current_server->server_names.push_back(name);
            }
            else if (key == "root")
                current_server->root = value;
            else if (key == "index")
            {
                std::istringstream iss(value);
                std::string f;
                while (iss >> f)
                    current_server->index_files.push_back(f);
            }
            else
                current_server->extra_directives[key] = value;
        }
        else
        {
            if (key == "include")
                includes.push_back(value);
        }
    }

    if (!block_stack.empty())
        throw std::runtime_error("Error: unclosed block(s) at end of file");
}
