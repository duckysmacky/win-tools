# compiler
CC = gcc
CFLAGS = -Wall

# dirs
SOURCE = src/commands
HEADERS = src/include
UTIL = src/utils
BIN = out/bin
OBJ = out/obj

# files
CMDS = ls touch grep
UTILS = $(UTIL)/arr-utils.c $(UTIL)/str-utils.c
OBJS = $(OBJ)/arr-utils.o $(OBJ)/str-utils.o

all: $(BIN)/ls $(BIN)/touch $(BIN)/grep
	@echo All bins finished compiling!

# TODO - fix make clean
clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

# bins
$(BIN)/ls: $(OBJS)
	@$(CC) $(SOURCE)/ls/*.c $^ -o $@ $(CFLAGS)
	@echo Built ls

$(BIN)/touch: $(OBJS)
	@$(CC) $(SOURCE)/touch/*.c $^ -o $@ $(CFLAGS)
	@echo Built touch

$(BIN)/grep: $(OBJS)
	@$(CC) $(SOURCE)/grep/*.c $^ -o $@ $(CFLAGS)
	@echo Built grep

# objs
objs: $(OBJS)
$(OBJ)/arr-utils.o: $(UTIL)/arr-utils.c
	@$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJ)/str-utils.o: $(UTIL)/str-utils.c
	@$(CC) -c $^ -o $@ $(CFLAGS)

# $(OBJ)/%.o: $(UTIL)/%.c
# $(CC) -c $< -o $@ $(CFLAGS)