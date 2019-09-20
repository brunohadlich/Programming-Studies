all:
	gcc soma_array.c -S
	mv soma_array.s soma_array_sem_especificar_otimizacao.s
	gcc main.c soma_array.c -o soma_array_sem_especificar_otimizacao
	
	gcc soma_array.c -S -O0
	mv soma_array.s soma_array_o0.s
	gcc main.c soma_array.c -O0 -o soma_array_o0
	
	gcc soma_array.c -S -O1
	mv soma_array.s soma_array_o1.s
	gcc main.c soma_array.c -O1 -o soma_array_o1
	
	gcc soma_array.c -S -O2
	mv soma_array.s soma_array_o2.s
	gcc main.c soma_array.c -O2 -o soma_array_o2
	
	gcc soma_array.c -S -O3
	mv soma_array.s soma_array_o3.s
	gcc main.c soma_array.c -O3 -o soma_array_o3

	gcc soma_array.c -S -march=native -O3
	mv soma_array.s soma_array_o3_native.s
	gcc main.c soma_array.c -march=native -O3 -o soma_array_o3_native
clear:
	rm soma_array_sem_especificar_otimizacao.s -f
	rm soma_array_sem_especificar_otimizacao -f
	rm soma_array_o0.s -f
	rm soma_array_o0 -f
	rm soma_array_o1.s -f
	rm soma_array_o1 -f
	rm soma_array_o2.s -f
	rm soma_array_o2 -f
	rm soma_array_o3.s -f
	rm soma_array_o3 -f
	rm soma_array_o3_native.s -f
	rm soma_array_o3_native -f
