all: util ls

util:
	gcc utils/str-utils.c -c -o out/obj/str-utils.o
	gcc utils/arr-utils.c -c -o out/obj/arr-utils.o

ls: util
	gcc src/ls/ls.c out/obj/str-utils.o out/obj/arr-utils.o -o out/bin/ls

touch:
	gcc src/touch/touch.c -o out/bin/touch
