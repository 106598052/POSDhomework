all: hw6

hw6: mainParser.o atom.o list.o node.o
ifeq (${OS}, Windows_NT)
	g++ -o hw6 mainParser.o atom.o list.o node.o -lgtest
else
	g++ -o hw6 mainParser.o atom.o list.o node.o -lgtest -lpthread
endif

mainParser.o: mainParser.cpp atom.h struct.h
	 	g++  -std=gnu++0x -c  mainParser.cpp
atom.o: atom.h atom.cpp
		g++ -std=gnu++0x -c atom.cpp
list.o: list.h list.cpp
		g++ -std=gnu++0x -c list.cpp
node.o: node.h node.cpp
		g++ -std=gnu++0x -c node.cpp
clean:
	rm -f *.o hw6
stat:
	wc *.h *.cpp
