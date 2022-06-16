
all:
	gcc -Wall -Werror -g -o huffcode huffcode.c
	
clean:
	rm -rf huffcode
