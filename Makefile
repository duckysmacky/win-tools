all: util ls touch grep

util:
	gcc utils/str-utils.c -c -o out/obj/str-utils.o
	gcc utils/arr-utils.c -c -o out/obj/arr-utils.o

ls:
	gcc src/ls/ls.c out/obj/str-utils.o out/obj/arr-utils.o -o out/bin/ls -Wall

touch:
	gcc src/touch/touch.c out/obj/arr-utils.o out/obj/str-utils.o -o out/bin/touch -Wall

grep:
	gcc src/grep/grep.c out/obj/str-utils.o -o out/bin/grep -Wall
