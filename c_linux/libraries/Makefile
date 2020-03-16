clear:
	rm -f bin/*
	rm -f libs/*
	rm -f objects/main.o
	rm -f objects/static/*
	rm -f objects/shared/*
	rm -f /usr/lib/libmath.so*

main.c:
	gcc -c src/main.c
	mv main.o objects/main.o

static: clear main.c
	gcc -c src/sum.c
	gcc -c src/div.c
	mv sum.o div.o objects/static/
	ar -rcs libs/libmath.a objects/static/sum.o objects/static/div.o
	gcc objects/main.o -Wno-all -Llibs -lmath -o bin/static_bin
	./bin/static_bin

compile_shared:
	gcc -c -fPIC src/sum.c
	gcc -c -fPIC src/div.c
	mv sum.o div.o objects/shared/
	gcc -shared objects/shared/sum.o objects/shared/div.o -Wl,-soname,libmath.so.1 -o libs/libmath.so.1.0.0

shared: clear main.c compile_shared
	gcc objects/main.o -Llibs -l:libmath.so.1.0.0 -o bin/shared_bin # -Llibs, procure libs no diretório ./libs
	ln -s libmath.so.1.0.0 libs/libmath.so.1 # libmath.so.1, soname buscado na execução de um programa
	LD_LIBRARY_PATH=./libs/ ./bin/shared_bin

shared2: clear main.c compile_shared
	ln -s libmath.so.1.0.0 libs/libmath.so # libmath.so é o nome que o compilador busca na etapa de linkagem 
	gcc objects/main.o -Llibs -lmath -o bin/shared_bin # -lmath == libmath.so
	ln -s libmath.so.1.0.0 libs/libmath.so.1 # libmath.so.1, soname buscado na execução de um programa
	LD_LIBRARY_PATH=./libs/ ./bin/shared_bin

shared3: clear main.c compile_shared
	cp libs/libmath.so.1.0.0 /usr/lib/
	ln -s /usr/lib/libmath.so.1.0.0 /usr/lib/libmath.so.1 # libmath.so.1 é o nome que o sistema busca na execução do programa
	ln -s /usr/lib/libmath.so.1 /usr/lib/libmath.so # libmath.so é o nome que o compilador busca na etapa de linkagem
	gcc objects/main.o -lmath -o bin/shared_bin # -lmath == libmath.so
	./bin/shared_bin

shared4: clear main.c compile_shared
	cp libs/libmath.so.1.0.0 /usr/lib/
	ldconfig -n /usr/lib #cria link simbólico entre soname e real name
	gcc objects/main.o -Llibs -l:libmath.so.1.0.0 -o bin/shared_bin
	./bin/shared_bin
