all: hw5

hw5: mainParser.o term.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainParser.o term.o list.o -lgtest
else
	g++ -o hw5 mainParser.o term.o list.o -lgtest -lpthread
endif

mainParser.o: mainParser.cpp atom.h struct.h
	 	g++  -std=gnu++0x -c  mainParser.cpp
term.o: term.h variable.h term.cpp
		g++ -std=gnu++0x -c term.cpp
list.o: list.h list.cpp
		g++ -std=gnu++0x -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
		del *.o *.exe
else
		rm -f *.o hw5
endif
