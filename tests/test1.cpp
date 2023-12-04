#include <iostream>

#include "../src/easycfg.h"

int main() {
    ezcfg::Parser cfgfile("tests/test1.ezcfg");
    std::map<std::string, std::string> config_data = {
        {"IP_addr", ""},
        {"Port", ""},
        {"size", ""}
    };
    cfgfile.initMap(&config_data);
    cfgfile.parse();

    // since no default value has been provided for IP_addr, the string will be of
    // length 0. Since EasyCfg doesn't provide a way  to set variables to empty strings,
    // we know that no definition for IP_addr has been provided in the config file.
    if (!config_data["IP_addr"].size())
        std::cout << "IP_addr has not been set!" << std::endl;

    for (const auto &pair : config_data) {
        std::cout << "Variable: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}