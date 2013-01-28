COMPILE = g++
EXE = s_mad
LIBS = -lGL -lGLU -lglut -lX11 -lXmu
LIBSDIR = -L/usr/X11R6/lib -L/usr/lib



all : main

main : main.cpp
	${COMPILE} main.cpp -o ${EXE} ${LIBS} ${LIBSDIR}

clean :
	rm -f ${EXE} *~ \#*\#

