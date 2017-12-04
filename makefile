all: hw7

hw7: mainIterator.o atom.o list.o struct.o term.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainIterator.o atom.o list.o struct.o term.o -lgtest
else
	g++ -o hw7 mainIterator.o atom.o list.o struct.o term.o -lgtest -lpthread
endif

mainIterator.o: mainIterator.cpp utIterator.h number.h
	g++ -std=gnu++11 -c mainIterator.cpp
atom.o: atom.cpp atom.h variable.h term.h
	g++ -std=gnu++11 -c atom.cpp
list.o:list.cpp list.h term.h
	g++ -std=gnu++11 -c list.cpp
struct.o:struct.cpp struct.h
	g++ -std=gnu++11 -c struct.cpp
term.o:term.cpp term.h
	g++ -std=gnu++11 -c term.cpp

clean:
	rm -f *.o hw7
stat:
	wc *.h *.cpp
