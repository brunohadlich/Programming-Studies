all:
	gcc -march=native -g -O3 -c sobel.c
	gcc -Wall -Wextra -g -march=native main.c sobel.h sobel.o -lm -o main

asm:
	gcc -g -static -no-pie -std=c99 -march=native main.c sobel.h my_sobel2.s -lm -o asm_main

clear:
	rm -f main
	rm -f asm_main
	rm -f sobel.o
