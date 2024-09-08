all: clear
	gcc -c extern_foo.c -o extern_foo.o
	gcc -c main.c -o main.o
	gcc extern_foo.o main.o -o main

clear:
	rm -f extern_foo.o main.o main
