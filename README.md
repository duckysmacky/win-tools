# Win-Tools

A collection of useful command line tools for Windows

## About

This project aims to add a bunch of useful commands for Windows. This includes ports of the most
popular UNIX commands to replace Windows default alternavies by adding more features, improving
perfomance and putting then closer to their original counterparts, as well as partially adding
some custom functionality

All commands are build based on Windows API for a more native feel and better perfomance. Recently
there was a switch from exclusive C codebase to mostly C++ code to improve speed, reduce complexity
and to mostly remove dangers of the C language like memory leaks. 

Current goal of the project is to optimise avaliable commands and bring the project to
a **stable release with those four**. After that it is planned to continue rebuilding from zero and
porting other popular UNIX commands for more native experience.

Any kind of contribution is very appreciateed and will be a huge help to project's future development

## Features

Win-tools is in a **very active development right now**, with currently only four commands implemented:
- `ls`
- `grep`
- `head`
- `touch`

Possible future commands (or their alternatives) to be added in the future are, but not limited to:
`tail`, `copyf`, `cp`, `mv`, `less`, `sed`, `sort`

There is some outdated documentation under each `src/<command>` directory, which will be updated
with project's development and hopefully by release will contain up to date information. It is also
planned for each command to have a complete `--help` option for documentation to be built in.

## Installation

For now the project is still in very early development, so there are **no public releases at the moment**.
You can build all of the binaries by yourself using Visual Studio 2022

All built binaries be found within the `bin/` in the corresponding target platform (32-bit or 64-bit)
directory. They can be added to your system's `PATH` to be used anywhere (some require for default Windows
aliases to be overritten, like `ls`)
