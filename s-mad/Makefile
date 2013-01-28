COMPILE = gcc
EXE = s-mad
LIBS = -lX11 -lXmu  `pkg-config --libs gtk+-2.0`
LIBSDIR = -L/usr/X11R6/lib -L/usr/lib `pkg-config --cflags gtk+-2.0`

all : main

main : main.c
	clear
	${COMPILE} main.c -Wall -o ${EXE} ${LIBS} ${LIBSDIR}
	@ echo " [OK] Compile"
clear :
	rm -f ./*~
	rm -f ./include/*~
	@ echo "\n [OK] Cleaner"

