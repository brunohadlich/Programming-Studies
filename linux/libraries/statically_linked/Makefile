CC=gcc
CFLAGS=-W -Wall -Wextra
EXEC=arithmetics
SRC_FOLDER=src
OBJ_FOLDER=obj
LIB_FOLDER=lib
SRC=$(wildcard $(SRC_FOLDER)/*.c)
OBJ=$(SRC:$(SRC_FOLDER)/%.c=$(OBJ_FOLDER)/%.o)
LIB=$(LIB_FOLDER)/arithmetics.a

all: $(EXEC) $(LIB)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

$(LIB): $(OBJ)
	[ -d $(LIB_FOLDER) ] || mkdir -p $(LIB_FOLDER)
	ar -cvq $(LIB) $(OBJ)

$(OBJ): $(SRC)
	[ -d $(OBJ_FOLDER) ] || mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $(SRC)
	mv *.o $(OBJ_FOLDER)/

clean:
	[ -d $(OBJ_FOLDER) ] && rm -rf $(OBJ_FOLDER)/*
	[ -d $(LIB_FOLDER) ] && rm -rf $(LIB_FOLDER)/*
	rm -rf $(EXEC)
