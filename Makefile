all:
	make util
	make ls

util:
	gcc utils/str-utils.c -c -o out/obj/str-utils.o
	gcc utils/arr-utils.c -c -o out/obj/arr-utils.o

ls:
	gcc src/ls/ls.c out/obj/str-utils.o out/obj/arr-utils.o -o out/bin/ls