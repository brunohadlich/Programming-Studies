remove_links:
	rm -f libs/libmath.so
	rm -f libs/libmath.so.1
	sudo rm -f /usr/lib/libmath.so
	sudo rm -f /usr/lib/libmath.so.1

clear: remove_links
	rm -f bin/*
	rm -f libs/*
	rm -f objects/main.o
	rm -f objects/static/*
	rm -f objects/shared/*
	sudo rm -f /usr/lib/libmath.so*

main.c:
	gcc -Iheaders -c src/main.c
	mv main.o objects/main.o

static: clear main.c
	gcc -c src/sum.c
	gcc -c src/div.c
	mv sum.o div.o objects/static/
	ar -rcs libs/libmath.a objects/static/sum.o objects/static/div.o
	gcc objects/main.o -Llibs -lmath -o bin/static_bin
	./bin/static_bin

compile_shared:
	gcc -c -fPIC src/sum.c
	gcc -c -fPIC src/div.c
	mv sum.o div.o objects/shared/
	#compila a biblioteca
	gcc -shared objects/shared/sum.o objects/shared/div.o -Wl,-soname,libmath.so.1 -o libs/libmath.so.1.0

shared_bin: remove_links main.c compile_shared
	#compila o executável
	gcc objects/main.o -Llibs -l:libmath.so.1.0 -o bin/shared_bin # -Llibs, procure libs no diretório ./libs
	#linka a biblioteca ao soname
	ln -s libmath.so.1.0 libs/libmath.so.1 # libmath.so.1, soname buscado na execução de um programa
	#executa
	LD_LIBRARY_PATH=./libs/ ./bin/shared_bin

shared_bin_2: remove_links main.c compile_shared
	#linka a biblioteca ao linker name
	ln -s libmath.so.1.0 libs/libmath.so # libmath.so é o linker name, nome que o compilador busca na etapa de linkagem 
	#compila o executável
	gcc objects/main.o -Llibs -lmath -o bin/shared_bin # -lmath == libmath.so
	#linka a biblioteca ao soname
	ln -s libmath.so.1.0 libs/libmath.so.1 # libmath.so.1, soname buscado na execução de um programa
	#executa
	LD_LIBRARY_PATH=./libs/ ./bin/shared_bin

shared_bin_3: remove_links main.c compile_shared
	sudo cp libs/libmath.so.1.0 /usr/lib/
	sudo ln -s /usr/lib/libmath.so.1.0 /usr/lib/libmath.so.1 # libmath.so.1 é o nome que o sistema busca na execução do programa
	sudo ln -s /usr/lib/libmath.so.1 /usr/lib/libmath.so # libmath.so é o nome que o compilador busca na etapa de linkagem
	gcc objects/main.o -lmath -o bin/shared_bin # -lmath == libmath.so
	./bin/shared_bin

shared_bin_4: remove_links main.c compile_shared
	sudo cp libs/libmath.so.1.0 /usr/lib/
	sudo ldconfig -n /usr/lib #cria link simbólico entre soname e real name
	gcc objects/main.o -Llibs -l:libmath.so.1.0 -o bin/shared_bin
	./bin/shared_bin

shared_bin_5: remove_links main.c compile_shared
	sudo cp libs/libmath.so.1.0 /usr/lib/
	sudo ldconfig -n /usr/lib #cria link simbólico entre soname e real name
	sudo ln -s /usr/lib/libmath.so.1 /usr/lib/libmath.so
	gcc objects/main.o -lmath -o bin/shared_bin
	./bin/shared_bin
