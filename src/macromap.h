#pragma once

#include <string>
#include <map>

namespace ezcfg
{
    struct {
        std::map<std::string, std::string> string_map;
        std::map<std::string, void(*)(std::string &out)> function_map;
    } macroMap;

    void initMacroMap();
    void setMacroMapAt(std::string &key, std::string &value);
    bool getMacroMapAt(std::string &key, std::string &out);

    namespace functions
    {
        void resolveMacroWDP(std::string &out);
    }
}