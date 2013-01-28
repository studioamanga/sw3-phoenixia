COMPILE = g++
EXE = phoenixia
CFLAGS  = -I/usr/include -Wall
LIBS = -lGL -lGLU -lglut -lX11 -lXmu -lfmod-3.74
LIBSDIR = -L/usr/X11R6/lib -L/usr/lib

all : main

main : sources/main.cpp
	clear
	$(COMPILE) sources/main.cpp -o $(EXE) $(CFLAGS) $(LIBS) $(LIBSDIR)
	@ echo " [OK] Compile"
clear :
	rm -f ./*~
	rm -f ./sources/*~
	rm -f ./s-mad/modelor/*~
	rm -f ./s-mad/*~
	rm -f ./s-mad/include/*~
	@ echo " [OK] Cleaner"
tar :
	tar -jcvf ../phoenix ../phoenix.tar.bz2
backup :
	tar -jcvf ../phoenix ../phoenix.backup.tar.bz2
code :
	make clear
	make backup
	emacs ./ &
