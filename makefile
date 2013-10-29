CC =			g++
CFLAGS =	-g -Wall -std=c++11 -O3
LFLAGS =	-lglut -lGL -lGLU -lm -lopencv_core -lopencv_highgui


HEA = $(shell find SRC/ -name *.hh -o -name *.hpp)
SRC = $(shell find SRC/ -name '*.cc')
OBJ = $(patsubst SRC/%.cc, OBJS/%.o, $(SRC))


EXEC = GeoAlps




.PHONY: all clean clear dox

all: build

build: $(OBJ)
	$(CC) $(LFLAGS) -o OBJS/$(EXEC) $^
	ln -s -f OBJS/GeoAlps .


$(OBJ): OBJS/%.o : SRC/%.cc $(HEA)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -r $(OBJ)

clear: clean
	rm -r OBJS/$(EXEC) $(EXEC)


################################################################################
# Generate doxygen documentation of file two.c using command file two.dox.
dox: src/examples/two.c src/examples/two.h
	rm -rf DOX
	doxygen src/examples/two.dox
#

