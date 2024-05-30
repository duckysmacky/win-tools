# A collection of Linux-ported command line tools for Windows

The goal of this project is to port most commonly used Linux commands to Windows, as they are not there in CMD or Powershell by default (with exceptions).

Most of these commands are their 1-to-1 replica of their Linux equivalents, but there are slight differences doe to OS specifics and my programming skills. Allthough the goal is to replicate these commands as accurate as possible, I still sometimes add my own additions into the mix.

## Installation

For now the project is still in very early development, so there are no public releases, but you can build binaries yourself:

1. Clone repo `git clone https://github.com/duckysmacky/win-tools.git`
2. Go into cloned repo `cd win-tools`
3. Build with `make all`
4. You are done!

All built binaries be found in `bin/` and can be added to your system's `PATH` to be used anywhere

## Features

All currently avaliable commands as well as future plans are listed below:

| Command               | Status | Options | Stability |
| :-------------------- |:------:| :-----: | :-------: |
| [`ls`](#ls)           | ✅    | ➖      | ✅       |
| [`ll (ls -l)`](#ls)   | ➖    | ❌      | ❌       |
| [`touch`](#touch)     | ✅    | ➖      | ✅       |
| [`grep`](#grep)       | ➖    | ➖      | ➖       |
| [`head`](#head)       | ✅    | ➖      | ✅       |
| [`tail`](#tail)       | ❌    | ❌      | ❌       |
| [`copyf`](#copyf)     | ❌    | ❌      | ❌       |
| [`cp`](#cp)           | ❌    | ❌      | ❌       |
| [`mv`](#mv)           | ❌    | ❌      | ❌       |
| [`less`](#less)       | ❌    | ❌      | ❌       |
| [`sed`](#sed)         | ❌    | ❌      | ❌       |
| [`sort`](#sort)       | ❌    | ❌      | ❌       |
| [`man`](#man)         | ❓     |         |           |
| [`ln`](#ln)           | ❓     |         |           |


| Emoji | Meaning          |
| :---: | ---------------- |
| ✅   | Fully Functional |
| ➖   | Semi-functional  |
| ❌   | Incomplete       |
| ❓    | Under question   |


## `ls`
Lists directory contents of files and other directories. *Much more prettier then the default Poweshell `ls` command.*

### Usage
```bash
Usage: ls [OPTIONS] [DIRECTORY]
```
By default lists content of current directory. Output is colored based on file type (blue - directory, green - file, yellow - executable, cyan - hidden files).

### Options
| Option | Description |
| :----- | :-----------|
| -h     | Show help information about this command
| -l	 | Long format that displays more detailed information (alias to `ll`)
| -a	 | Show hidden files
| -A     | Show hidden files together with `..` and `.`
| -t	 | Sort by last modification time (recent first)
| -r	 | Reverse order of listing
| -R	 | List files and directories recursively, including subdirectories
| -s	 | Sort by their sizes (bigger first)
| -i	 | Show index of each file
| -g	 | Display the group ownership instead of the owner
| -H	 | Print file sizes in human-readable format (1K, 234M, 2G)
| -d	 | List directories themselves, rather than their contents

[Source](https://www.geeksforgeeks.org/ls-command-in-linux/)

## `touch`
Used to create, change and modify the timestamps of a file. The file created using the touch command is empty. This command can be used when the user doesn’t have data to store at the time of file creation.

### Usage
```bash
Usage: touch [OPTIONS] <FILE_NAME>...
```
By default creates a specified file, can enter multiple filenames for simultanious file creation. If used on already existing file, updates its access and modify time to current.

### Options
| Option | Description |
| :----- | :-----------|
| -h     | Show help information about this command
| -a	 | Change only the access time
| -m	 | Change only the modify time
| -d	 | Set access and moify time from passed argument string
| -r	 | Set access and moify time based on another file
| -c	 | Supress file creation if doesnt exist
| -t	 | Create file using specified YYMMDDHHMM

[Source](https://www.geeksforgeeks.org/touch-command-in-linux-with-examples/)

## `grep`
Used for searching and manipulating text patterns within files. Searches the file line by line for the given pattern and prints matched lines. 

### Usage
```bash
Usage: grep [OPTIONS] <PATTERN> [FILE_NAME]...
```
By default, if no file is specfied, will search the current directory for given pattern, else will search for the pattern in each of given files. Is not a Regex pattern by default.

### Options
| Option | Description |
| :----- | :-----------|
| -h     | Show help information about this command
| -c     | Print only the number of matched lines
| -i     | Ignore case (upper/lower)
| -n     | Show line number of found pattern
| -v     | Print only the lines which didn't match any pattern
| -w     | Only match the whole word
| -o     | Print only matching parts of the line
| -R     | Recursively search current/given directory
| -e     | Supply a **Regex** pattern to search
| -f     | Use a pattern from given file

[Source](https://www.geeksforgeeks.org/grep-command-in-unixlinux/)

## `head`
Prints the top content of a given file. Can be used to view either x amount of lines or bytes in a file, instead of printing the whole file content.

### Usage
```bash
Usage: head [OPTIONS] <FILE_NAME>...
```
By default, it prints the first 10 lines of the specified files. If more than one file name is provided then data from each file is preceded by its file name. 

### Options
| Option | Description |
| :----- | :-----------|
| -h     | Show help information about this command
| -v     | Always print file names
| -q     | Don't print file names
| -n     | Number of lines from top to print
| -c     | Number of bytes to print

[Source](https://www.geeksforgeeks.org/head-command-linux-examples/)

## Known Issues

- Memory leaks 💀
- Trying to `ls -R` or `grep` in a really big directory crashes the program
- Trying to `ls -R` the `.git` directory crashes the program 

If you find any other bugs please submit them [here](https://github.com/duckysmacky/win-tools/issues).