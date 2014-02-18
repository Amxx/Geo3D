CC =     	g++
CFLAGS =	-g -Wall -O3
LFLAGS =	-lglut -lGL -lGLU -lm



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
	BROWSER =			safari
	VIEWER =			
endif
# ============ LINUX ============================================================
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
	GL_LIBDIRS =
	GL_INCLUDE =  -I. -I/usr/include
	BROWSER =			firefox
	VIEWER =			evince
endif
# ===============================================================================



HEA = $(shell find SRC/ -name *.hh -o -name *.hpp)
SRC = $(shell find SRC/ -name '*.cc')
OBJ = $(patsubst SRC/%.cc, OBJS/%.o, $(SRC))

EXEC = Delaunay



.PHONY: all clean clear doc opendoc rapport openrapport

all: mkdir build doc rapport

mkdir :
	mkdir -p OBJS/geometry OBJS/structure OBJS/tools OBJS/pdf

build: $(OBJ)
	$(CC) $(LFLAGS) $(GL_LIBDIRS) -o OBJS/$(EXEC) $^
	ln -s -f OBJS/$(EXEC) .

$(OBJ): OBJS/%.o : SRC/%.cc $(HEA) makefile
	$(CC) $(CFLAGS) $(GL_INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ)

clear: clean
	rm -rf OBJS/$(EXEC) OBJS/pdf DOCS/ $(EXEC) Rapport.pdf


doc: $(HEA)
	doxygen SRC/delaunay.dox

opendoc: doc
	$(BROWSER) DOCS/html/index.html 
	
rapport: mkdir RAPPORT/Rapport.tex
	cd RAPPORT && pdflatex -output-directory=../OBJS/pdf/ Rapport.tex 
	ln -s -f OBJS/pdf/Rapport.pdf .

openrapport: rapport
	$(VIEWER) OBJS/pdf/Rapport.pdf
