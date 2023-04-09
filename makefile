# Example 14
EXE=final

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
final.o: final.c WGP.h
fatal.o: fatal.c WGP.h
errcheck.o: errcheck.c WGP.h
print.o: print.c WGP.h
loadtexbmp.o: loadtexbmp.c WGP.h
projection.o: projection.c WGP.h
icosahedron.o: icosahedron.c WGP.h
mill.o: mill.c WGP.h
bridge.o: bridge.o WGP.h
shader.o: shader.o WGP.h
#  Create archive
WGP.a:fatal.o errcheck.o print.o loadtexbmp.o projection.o icosahedron.o mill.o bridge.o shader.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
final:final.o   WGP.a
	gcc $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
