utils:
	gcc utils/str-utils.c -c -o out/obj/str-utils.o

ls:
	gcc src/ls/ls.c out/obj/str-utils.o -o out/bin/ls