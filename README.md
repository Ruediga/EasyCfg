# EasyCfg

A simple, lightweight and very easy to use configuration file parser.

Originally made for my own purposes.

## How to add to your project

Just include the header "easycfg.h" and get started!

```cpp
#include <easycfg.h>
```

## Syntax

### Variables

Variables that can be set need to be configured in the cpp file:

```cpp
#include <easycfg/easycfg.h>

int main() {
    ezcfg::Parser cfgfile("path/to/your/config/file.ezcfg");
    std::map<std::string, std::string> config_data = {
        {"key1", ""},
        {"key2", ""}
    };
    cfgfile.initMap(config_data);
}
```

Then you can set them in the .ezcfg file

```
key1: some_value
key2: another_value
```

### Macros

List of predefined macros (evaluated during runtime)

```
ezcfg_string: <EZCFG>   # evaluates to "EasyCfg"
cwd_path: <EP>         # absolute path to current working directory
```

It's also possible to overwrite default macros or define new macros:

```
$<MACRO_NAME>: new_val  # overwrite / set value of MACRO_NAME
```

### Comments

you can create single line comments like this:

```
path: C:/               # This is a comment
```

### More parsing details
EasyCfg removes whitespaces during parsing, which means that variable names or values can't contain whitespaces either:

```
lang uage : EN - DE
language:EN-DE          # equals the above
```

Important details:
- The Parser is case sensitive
- If a value is assigned multiple times, the latest definition is used
- Parsed information is stored in a std::map<std::string, std::string>
- Values get parsed first

## Examples

#### main.cpp
```cpp
#include <iostream>
#include <easycfg/easycfg.h>

int main() {
    ezcfg::Parser cfgfile("path/to/your/config/file.ezcfg");
    std::map<std::string, std::string> config_data = {
        {"IP_addr", ""},
        {"Port", ""},
        {"serverroot", ""}
    };
    cfgfile.initMap(config_data);

    // parse the file
    if (!cfgfile.parse()) {
        std::cout << "Error parsing file!" << std::endl;
        return -1;
    }

    if (!config_data["IP_addr"].size())
        std::cout << "IP_addr has not been set!" << std::endl;

    for (const auto &pair : config_data) {
        std::cout << "Variable: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}
```

#### config.ezcfg
```
$<SERVROOT>: servroot/          # define a macro

IP_addr: 127.0.0.1              # set variables
Port: 443

serverroot: <EP>/<SVROOT>      # accessing macros
```


## Implementation

Details on the algorithm used by the parsers can be found in https://github.com/Ruediga/EasyCfg/docs/implementation.md