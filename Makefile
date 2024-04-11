# TODO - make better makefile
ARGS = -Wall
OBJS := out/obj/arr-utils.o out/obj/str-utils.o

all: util ls touch grep

clean:
	rm out/bin/*

util:
	gcc utils/str-utils.c -c -o out/obj/str-utils.o
	gcc utils/arr-utils.c -c -o out/obj/arr-utils.o

ls:
	gcc src/ls/ls.c -o out/bin/ls $(OBJS) $(ARGS)

touch:
	gcc src/touch/touch.c -o out/bin/touch $(OBJS) $(ARGS)

grep:
	gcc src/grep/grep.c -o out/bin/grep $(OBJS) $(ARGS)
