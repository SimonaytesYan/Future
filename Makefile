RELEASE_FLAGS = -O2 -std=c++2a
SANITIZER_FLAGS = -g -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
FLAGS 		  = $(SANITIZER_FLAGS)
COMPILER      = g++

SRC = Src/
BIN = Bin/
OBJ = Obj/

ELF_FILE = $(BIN)run

all: create_folders
	$(COMPILER) $(FLAGS) $(SRC)main.cpp -o $(ELF_FILE)

update_submodules:
	git submodule update --init --recursive --remote

run: create_folders
	./$(ELF_FILE)

create_folders:
	-mkdir $(BIN)
	-mkdir $(OBJ)

clean:
	-rm -r $(BIN)
	-rm -r $(OBJ)