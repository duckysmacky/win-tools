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

Four commands are currently avaliable:
- `ls`
- `grep`
- `head`
- `touch`

There is currently some **outdated documentation** under each `src/commands/<command>` directory in a README
file. Please refer to each command's `--help` menu for the up-to-date documentation and usage.

## Installation

For now the project is still in development, so there are no public releases at the moment. Instead, you 
can build all of the binaries by yourself using Visual Studio 2022 or `msbuild` command using the Developer's 
Power Shell:

```shell
git clone https://github.com/duckysmacky/win-tools.git
cd win-tools
msbuild -p:Configuration=Release
```

All built binaries be found within the `build/bin/` in the corresponding target platform (32-bit or 64-bit)
directory. They can be added to your system's `PATH` to be used anywhere (some require for default Windows
aliases to be overritten, like `ls`)
