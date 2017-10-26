all: hw4

hw4: mainList.o term.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 mainList.o term.o atom.o -lgtest
else
	g++ -o hw4 mainList.o term.o atom.o -lgtest -lpthread
endif

mainList.o: mainList.cpp utList.h
	g++ -std=gnu++11 -c mainList.cpp
term.o: term.cpp term.h variable.h
	g++ -std=gnu++11 -c term.cpp
atom.o: atom.cpp atom.h term.h
	g++ -std=gnu++11 -c atom.cpp

clean:
	rm -f *.o hw4
stat:
	wc *.h *.cpp
