# A collection of useful command line tools

Most of these tools are just their Linux equivalent, as they are not there in CMD or Powershell by default (with exceptions)

## Install

For now the project is still in very early development, so there are no public releases, but you can build binaries yourself:

1. Clone repo `git clone https://github.com/duckysmacky/win-tools.git`
2. Go into cloned repo `cd win-tools`
3. Build with `make all`
4. You are done!

All built binaries be found in `bin/` and can be added to your system's `PATH` to be used anywhere

## Features

All currently avaliable tools and features are listed below, as well as future plans:

### Linux commands
- [X] ls
- [X] touch
- [X] grep
- [ ] copyf
- [ ] cp
- [ ] mv
- [ ] less
- [ ] sed
- [ ] sort
- [ ] man (?)
- [ ] ln (?)

## Known Issues

1. `ls -l` doesn't work time to time
2. Trying to `ls -R` or `grep` in a really big directory crashes the program
3. Trying to `ls -R` the `.git` directory crashes the program 

If you find any other bugs please submit them in [issues](https://github.com/duckysmacky/win-tools/issues). It would mean world to me, if I can release these tools without any bugs!
