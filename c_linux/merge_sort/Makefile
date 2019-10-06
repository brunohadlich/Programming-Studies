all:
	gcc main.c utils.c merge_sort.c -march=native -O3 -o single_thread_merge_sort
	gcc main.c utils.c parallel_merge_sort.c -march=native -O3 -pthread -o multi_thread_merge_sort
clear:
	rm -f single_thread_merge_sort multi_thread_merge_sort
test:
	echo "Executing single_thread_merge_sort"
	./single_thread_merge_sort
	echo "Executing multi_thread_merge_sort"
	./multi_thread_merge_sort
