all: hw4

hw4: mainList.o term.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 mainList.o term.o atom.o -lgtest
else
	g++ -o hw4 mainList.o term.o atom.o -lgtest -lpthread
endif

#utList:	mainList.o term.o atom.o
#	g++	-o	utList mainList.o term.o atom.o -lgtest -lpthread
#utAtom: mainAtom.o atom.o term.o
#	g++	-o	utAtom mainAtom.o	term.o atom.o -lgtest -lpthread
#utVariable: mainVariable.o atom.o term.o
#	g++	-o	utVariable mainVariable.o	term.o atom.o -lgtest -lpthread

mainList.o: mainList.cpp utList.h
	g++ -std=gnu++11 -c mainList.cpp
#mainVariable.o: mainVariable.cpp utVariable.h variable.h term.h
#	g++ -std=c++11 -c mainVariable.cpp
#mainAtom.o: mainAtom.cpp utAtom.h
#	g++ -std=c++11 -c mainAtom.cpp
term.o: term.cpp term.h variable.h
	g++ -std=gnu++11 -c term.cpp
atom.o: atom.cpp atom.h term.h
	g++ -std=gnu++11 -c atom.cpp
#variable.o: variable.h term.h

clean:
	rm -f *.o hw4
stat:
	wc *.h *.cpp
