# ls
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