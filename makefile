all: hw5

hw5: mainParser.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainParser.o atom.o -lgtest
else
	g++ -o hw5 mainParser.o atom.o -lgtest -lpthread
endif

mainParser.o: mainParser.cpp utParser.h struct.h scanner.h parser.h list.h
	g++ -std=gnu++0x -c mainParser.cpp
atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp

clean:
	rm -f *.o hw5
stat:
	wc *.h *.cpp
