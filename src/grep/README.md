# grep
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