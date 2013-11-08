CC =			g++
CFLAGS =	-g -Wall -O3
LFLAGS =	-lglut -lGL -lGLU -lm -lopencv_core -lopencv_highgui


GCC_VERSION_GE_47 = $(shell g++ -dumpversion | gawk '{print $$1>=4.7?"1":"0"}')
ifeq ($(GCC_VERSION_GE_47),1)
	CFLAGS +=-std=c++11 -DCPP11
endif


HEA = $(shell find SRC/ -name *.hh -o -name *.hpp)
SRC = $(shell find SRC/ -name '*.cc')
OBJ = $(patsubst SRC/%.cc, OBJS/%.o, $(SRC))

EXEC = Geo3D



.PHONY: all clean clear dox

all: build
	
build: $(OBJ)
	$(CC) $(LFLAGS) -o OBJS/$(EXEC) $^
	ln -s -f OBJS/$(EXEC) .


$(OBJ): OBJS/%.o : SRC/%.cc $(HEA) makefile
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

