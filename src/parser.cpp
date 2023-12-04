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

    initMacroMap();
}

bool ezcfg::Parser::parse()
{
    std::ifstream file(p_file_src_path);

    if (!file.is_open())
        std::cerr << p_file_src_path << " cannot be read from!" << std::endl;

    std::string line;
    int lineIndex = 1;
    bool success = true;
    while (std::getline(file, line))
    {
        if (!p_parseLine(line, lineIndex))
            success = false;

        lineIndex++;
    }

    file.close();

    return success;
}

bool ezcfg::Parser::p_parseLine(const std::string &line_, int lineIndex)
{
    std::string line = line_;
    p_rmvWhitspacesAndLFs(line);

    // throw away empty lines and commented out lines
    if (line.empty()) {
        return false;
    }

    // remove comment
    size_t p = line.find('#');
    line = line.substr(0, p);

    if (line.empty()) {
        return false;
    }

    if (functions::countOccurrencesOfCharInString(line, ':') != 1) {
        std::cout << "SYNTAX::ERROR: Multiple / No occurences of \':\' found in line "
            << lineIndex << std::endl;
        return false;
    }

    size_t colonPos = line.find(':');
    std::string key = line.substr(0, colonPos);
    std::string value = line.substr(colonPos + 1);

    // value
    value = replaceKeys(value, lineIndex);

    // key
    // macro definition
    if (key[0] == '$') {
        // valid
        if (key.size() >= 3) {
            int countbigger = functions::countOccurrencesOfCharInString(key, '>');
            int countsmaller = functions::countOccurrencesOfCharInString(key, '<');
            // valid
            if (countbigger == 1 && countsmaller == 1) {
                size_t starting_pos = key.find_first_of('<');
                size_t end_pos = key.find_first_of('>');
                // valid
                if (starting_pos == 1 && end_pos == key.size() - 1) {
                    // -2
                    std::string new_macro_name = key.substr(starting_pos + 1, end_pos - 2);
                    setMacroMapAt(new_macro_name, value);
                    return true;
                }
                else {
                    std::cout << "SYNTAX::ERROR: macro definition syntax is $<MACRO_NAME>:MACRO_VALUE in line "
                        << lineIndex << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "SYNTAX::ERROR: macro definition syntax is $<MACRO_NAME>:MACRO_VALUE in line "
            << lineIndex << std::endl;
            return false;
            }
        }
        else {
            std::cout << "SYNTAX::ERROR: macro definition error in line "
            << lineIndex << std::endl;
            return false;
        }
    }
    // implement macro inserting

    // setting a variable
    auto it = p_variable_map->find(key);
    if (it == p_variable_map->end()) {
        std::cout << "PARSING::ERROR: " << key << " doesn't exist!" << std::endl;
        return false;
    }
    else {
        p_variable_map->at(key) = value;
    }

    return true;
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

// [TODO] rewrite and better error messages
std::string ezcfg::Parser::replaceKeys(const std::string &input, int lineIndex)
{
    std::string result;
    size_t pos = 0;
    size_t start = 0;
    size_t end = 0;

    while ((start = input.find('<', pos)) != std::string::npos) {
        end = input.find('>', start);
        if (end == std::string::npos) {
            // If '>' is not found, the syntax is incorrect
            std::cerr << "Syntax error: '>' not found after '<' in line " << lineIndex << std::endl;
            return "";
        }

        result += input.substr(pos, start - pos); // Append text before '<'

        std::string key = input.substr(start + 1, end - start - 1);
        std::string out;
        // if the key exists
        if (getMacroMapAt(key, out)) {
            result += out;
        }
        else {
            std::cerr << "Key '" << key << "' not found in defined values" << std::endl;
            return "";
        }

        pos = end + 1;
    }

    result += input.substr(pos); // Append remaining text after last '>'
    return result;
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