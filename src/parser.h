#pragma once

#include <map>
#include <string>

namespace ezcfg
{
    class Parser
    {
    public:
        Parser(const char *config_file_path);
        ~Parser();

        void initMap(std::map<std::string, std::string> *config_map);

        void parse();

    private:
        const char *p_file_src_path;
        std::map<std::string, std::string> *p_variable_map;
        std::map<std::string, std::string> macroMap;

        void p_parseLine(const std::string &line_, int lineIndex);
        void p_rmvWhitspacesAndLFs(std::string &str);
    };

    namespace functions
    {
        int countOccurrencesOfCharInString(const std::string &str, char target);
    }
}