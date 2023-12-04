#include "macromap.h"

#include <filesystem>

// All default macros are defined and function mapped here
void ezcfg::initMacroMap()
{
    // function mapping
    macroMap.function_map["EP"] = functions::resolveMacroWDP;

    // string mapping
    macroMap.string_map["EZCFG"] = "EasyCfg";
}

void ezcfg::setMacroMapAt(std::string &key, std::string &value)
{
    auto iterator = macroMap.function_map.find(key);
    if (iterator != macroMap.function_map.end()) {
        macroMap.function_map[key] = nullptr;
    }

    macroMap.string_map[key] = value;
}

// return true if macro exists and has been replaced successfully
// return false if macro doesn't exist
bool ezcfg::getMacroMapAt(std::string &key, std::string &out)
{
    auto iterator = macroMap.function_map.find(key);
    if (iterator != macroMap.function_map.end()) {
        macroMap.function_map[key](out);
        return true;
    }
    auto iterator2 = macroMap.string_map.find(key);
    if (iterator2 != macroMap.string_map.end()) {
        out = macroMap.string_map[key];
        return true;
    }
    return false;
}

void ezcfg::functions::resolveMacroWDP(std::string &out)
{
    std::filesystem::path cwd = std::filesystem::current_path();
    out = cwd.string();
}
