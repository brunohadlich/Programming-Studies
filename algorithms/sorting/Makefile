base_objects: array.c main.c
	gcc -c array.c
	gcc -c main.c

bubble_sort.o: bubble_sort.c
	gcc -c bubble_sort.c

bubble_sort: base_objects bubble_sort.o
	gcc bubble_sort.o array.o main.o -o bubble_sort

insertion_sort.o: insertion_sort.c
	gcc -c insertion_sort.c

insertion_sort: base_objects insertion_sort.o
	gcc insertion_sort.o array.o main.o -o insertion_sort

selection_sort.o: selection_sort.c
	gcc -c selection_sort.c

selection_sort: base_objects selection_sort.o
	gcc selection_sort.o array.o main.o -o selection_sort

all: bubble_sort insertion_sort selection_sort

clear:
	rm -f *.o bubble_sort insertion_sort selection_sort