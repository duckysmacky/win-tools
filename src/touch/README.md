# touch
Used to create, change and modify the timestamps of a file. The file created using the touch command is empty. This command can be used when the user doesn’t have data to store at the time of file creation.

### Usage
```bash
Usage: touch [OPTIONS].. <FILE>...
```
By default creates a specified file, can enter multiple filenames for simultanious file creation. If used on already existing file, updates its access and modify time to current.

### Options
| Option | Description |
| :----- | :-----------|
| -V     | Show command version information
| -h     | Show help information about this command
| -a	 | Change only the access time
| -m	 | Change only the modify time
| -d	 | (TODO) Set access and moify time from passed argument string
| -r	 | (TODO) Set access and moify time based on another file
| -c	 | (TODO) Supress file creation if doesnt exist
| -t	 | (TODO) Create file using specified YYMMDDHHMM

[Source](https://www.geeksforgeeks.org/touch-command-in-linux-with-examples/)