# TODO - make better makefile
# compiler
CC = gcc
CFLAGS = -Wall

# dirs
SOURCE = src/commands
HEADERS = src/headers
UTIL = src/util
BIN = out/bin
OBJ = out/obj

# files
BINS = $(BIN)/ls $(BIN)/touch $(BIN)/grep
UTILS = $(UTIL)/arr-utils.c $(UTIL)/str-utils.c
OBJS = $(OBJ)/arr-utils.o $(OBJ)/str-utils.o

all: bins

clean:
	rm $(BIN)/*
	rm $(OBJ)/*

# bins
bins: $(BINS)
$(BIN)/ls: $(OBJS)
	$(CC) $(SOURCE)/ls/*.c $^ -o $@ $(CFLAGS)

$(BIN)/touch: $(OBJS)
	$(CC) $(SOURCE)/touch/*.c $^ -o $@ $(CFLAGS)

$(BIN)/grep: $(OBJS)
	$(CC) $(SOURCE)/grep/*.c $^ -o $@ $(CFLAGS)

# objs
objs: $(OBJS)
$(OBJ)/arr-utils.o: $(UTIL)/arr-utils.c
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJ)/str-utils.o: $(UTIL)/str-utils.c
	$(CC) -c $^ -o $@ $(CFLAGS)

# $(OBJ)/%.o: $(UTIL)/%.c
# $(CC) -c $< -o $@ $(CFLAGS)