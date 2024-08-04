# Win-Tools

A collection of useful command line tools for Windows

The goal of this project is to port most commonly used Linux commands to Windows, as they are not there in CMD or Powershell by default (with exceptions)

Most of these commands are their 1-to-1 replica of their Linux equivalents, but there are slight differences doe to OS specifics and my programming skills. Allthough the goal is to replicate these commands as accurate as possible, I still sometimes add my own additions into the mix

## Installation

For now the project is still in very early development, so there are no public releases for now. But you can build all of the binaries by yourself using Visual Studio 2022 (solution)

All built binaries be found within the `bin/` in the corresponding target platform (32-bit or 64-bit) directory. They can be added to your system's `PATH` to be used anywhere

## Features

Documentation for each command can be found under `src/[command]/README.md`. Below are listed all of the currently implemented commands and their avaliable features

| Command               | Status | Options | Stability |
| :-------------------- |:------:| :-----: | :-------: |
| [`ls`](#ls)           | ✅    | ➖      | ✅       |
| [`ll (ls -l)`](#ls)   | ➖    | ❌      | ❌       |
| [`touch`](#touch)     | ✅    | ➖      | ✅       |
| [`grep`](#grep)       | ➖    | ➖      | ➖       |
| [`head`](#head)       | ✅    | ➖      | ✅       |
<!-- | [`tail`](#tail)       | ❌    | ❌      | ❌       | -->
<!-- | [`copyf`](#copyf)     | ❌    | ❌      | ❌       | -->
<!-- | [`cp`](#cp)           | ❌    | ❌      | ❌       | -->
<!-- | [`mv`](#mv)           | ❌    | ❌      | ❌       | -->
<!-- | [`less`](#less)       | ❌    | ❌      | ❌       | -->
<!-- | [`sed`](#sed)         | ❌    | ❌      | ❌       | -->
<!-- | [`sort`](#sort)       | ❌    | ❌      | ❌       | -->

| Emoji | Meaning          |
| :---: | ---------------- |
| ✅   | Fully Functional |
| ➖   | Semi-functional  |
| ❌   | Incomplete       |
| ❓    | Under question   |

## Known Issues

- Memory leaks 💀
- Trying to `ls -R` or `grep` in a really big directory crashes the program
- Trying to `ls -R` the `.git` directory crashes the program 

If you find any other bugs please submit them [here](https://github.com/duckysmacky/win-tools/issues).