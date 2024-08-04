# head
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