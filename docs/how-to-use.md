## How to add to your project

[TODO]

## Syntax

#### Macros

List of predefines macros (evaluated during runtime)

> absolute_executable_path: $EP # absolute path of the executable being run (string)

> working_directory_path: $WDP # absolute path to current working directory

It's also possible to overwrite default macros or define new macros:

> ($MACRO_NAME): new_value # overwrite / set value of MACRO_NAME

#### Comments

you can create single line comments like this:

> path: C:/ # This is a comment

#### Parsing information
EasyCfg removes whitespaces during parsing, which means that variable names or values can't contain whitespaces either:

> lang uage : EN - DE

> language:EN-DE # equals the above

## Usage Examples

[TODO]