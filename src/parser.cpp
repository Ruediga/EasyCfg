#include "parser.h"
#include "macromap.h"

#include <fstream>
#include <filesystem>
#include <iostream>

ezcfg::Parser::Parser(const char *config_file_path)
    : p_file_src_path{config_file_path}, p_variable_map{nullptr}
{
    if (!std::filesystem::exists(p_file_src_path))
        std::cerr << p_file_src_path << " cannot be found!" << std::endl;
}

ezcfg::Parser::~Parser()
{
}

void ezcfg::Parser::initMap(std::map<std::string, std::string> *config_map)
{
    p_variable_map = config_map;
}

void ezcfg::Parser::parse()
{
    std::ifstream file(p_file_src_path);

    if (!file.is_open())
        std::cerr << p_file_src_path << " cannot be read from!" << std::endl;

    std::string line;
    int lineIndex = 1;
    while (std::getline(file, line))
    {
        p_parseLine(line, lineIndex);
        lineIndex++;
    }

    file.close();
}

void ezcfg::Parser::p_parseLine(const std::string &line_, int lineIndex)
{
    std::string line = line_;
    p_rmvWhitspacesAndLFs(line);

    // throw away empty lines and commented out lines
    if (line.empty()) {
        return;
    }

    // remove comment
    size_t p = line.find('#');
    line = line.substr(0, p);

    if (line.empty()) {
        return;
    }

    if (functions::countOccurrencesOfCharInString(line, ':') != 1) {
        // [TODO]
        std::cout << "SYNTAX::ERROR: Multiple / No occurences of \':\' found in line "
            << lineIndex << std::endl;
        return;
    }

    size_t colonPos = line.find(':');
    std::string key = line.substr(0, colonPos);
    std::string value = line.substr(colonPos + 1);

    // macro definition [TODO] out of range checks
    if (key[0] == '~') {
        if (key[1] == '$') {
            std::string macro_name = key.substr(2);
            setMacroMapAt(macro_name, value);
            return;
        }
    }
    // implement macro inserting

    // setting a variable
    auto it = p_variable_map->find(key);
    if (it == p_variable_map->end()) {
        // [TODO]
        std::cout << "PARSING::ERROR: " << key << " doesn't exist!" << std::endl;
    }
    else {
        p_variable_map->at(key) = value;
    } 
}

void ezcfg::Parser::p_rmvWhitspacesAndLFs(std::string &str_)
{
    std::string str = "";
    for (const char chr : str_)
    {
        if (chr != ' ' && chr != '\n' && chr != '\r')
            str += chr;
    }
    str_ = str;
}

namespace ezcfg
{
    namespace functions
    {
        int countOccurrencesOfCharInString(const std::string &str, char target)
        {
            int count = 0;
            for (char c : str)
            {
                if (c == target)
                    count++;
            }
            return count;
        }
    }
}