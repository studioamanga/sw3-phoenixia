COMPILE = g++
EXE = phoenixia
LIBS = -lGL -lGLU -lglut -lX11 -lXmu
LIBSDIR = -L/usr/X11R6/lib -L/usr/lib

all : main

main : main.cpp
	clear
	${COMPILE} main.cpp -O2 -o ${EXE} ${LIBS} ${LIBSDIR}
	@ echo " [OK] Compile"
clear :
	rm ./*~
	rm ./sources/*~
	@ echo " [OK] Cleaner"
clean :
	rm -f ${EXE} *~ \#*\#

