CC =     g++
CFLAGS = -g -Wall -O3
LFLAGS = -lglut -lGL -lGLU -lm



GCC_VERSION_GE_47 = $(shell g++ -dumpversion | awk '{print $$1>=4.7?"1":"0"}')
ifeq ($(GCC_VERSION_GE_47),1)
	CFLAGS += -std=c++11 -DCPP11
endif

CFLAGS += -DOPENCV
LFLAGS += -lopencv_core -lopencv_highgui



# ============ MAC OS ===========================================================
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Apple")),)
	GL_LIBDIRS =	-L. -L/usr/X11/lib -L/usr/local/lib -L"/System/Library/Frameworks/OpenGL.framework/Libraries" -framework GLUT -framework OpenGL
	GL_INCLUDE =	-I/usr/X11/include
endif
# ============ LINUX ============================================================
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
	GL_LIBDIRS =
	GL_INCLUDE =   -I. -I/usr/include
endif
# ===============================================================================



HEA = $(shell find SRC/ -name *.hh -o -name *.hpp)
SRC = $(shell find SRC/ -name '*.cc')
OBJ = $(patsubst SRC/%.cc, OBJS/%.o, $(SRC))

EXEC = Geo3D



.PHONY: all clean clear dox

all: mkdir build
	
mkdir :
	mkdir -p OBJS/geometry OBJS/structure OBJS/tools
	
build: $(OBJ)
	$(CC) $(LFLAGS) $(GL_LIBDIRS) -o OBJS/$(EXEC) $^
	ln -s -f OBJS/$(EXEC) .

$(OBJ): OBJS/%.o : SRC/%.cc $(HEA) makefile
	$(CC) $(CFLAGS) $(GL_INCLUDE) -c $< -o $@

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

