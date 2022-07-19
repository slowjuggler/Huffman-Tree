all: huff_func.c huff_main.c huffcode.h
	gcc -o huffcode -Wall -Wextra huff_main.c huff_func.c
