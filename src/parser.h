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

        // return false on parsing failure
        bool parse();

    private:
        std::string error_log;
        const char *p_file_src_path;
        std::map<std::string, std::string> *p_variable_map;
        std::map<std::string, std::string> macroMap;

        bool p_parseLine(const std::string &line_, int lineIndex);
        void p_rmvWhitspacesAndLFs(std::string &str);
        std::string replaceKeys(const std::string& input, int lineIndex);
    };

    namespace functions
    {
        int countOccurrencesOfCharInString(const std::string &str, char target);
    }
}