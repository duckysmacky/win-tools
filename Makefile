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

all: $(BINS)

clean:
	rm $(BIN)/*
	rm $(OBJ)/*

# bins
$(BIN)/ls: $(OBJS)
	$(CC) $(SOURCE)/ls/*.c $^ -o $@ $(CFLAGS)

$(BIN)/touch: $(OBJS)
	$(CC) $(SOURCE)/touch/*.c $^ -o $@ $(CFLAGS)

$(BIN)/grep: $(OBJS)
	$(CC) $(SOURCE)/grep/*.c $^ -o $@ $(CFLAGS)

# objs
$(OBJ)/arr-utils.o:
	$(CC) $(UTIL)/arr-utils.c -c -o $@ $(CFLAGS)

$(OBJ)/str-utils.o:
	$(CC) $(UTIL)/str-utils.c -c -o $@ $(CFLAGS)