all: hw2

hw2: mainTerm.o number.o atom.o variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o number.o atom.o variable.o -lgtest
else
	g++ -o hw2 mainTerm.o number.o atom.o variable.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h number.h
	g++ -std=gnu++11 -c mainTerm.cpp
number.o: number.h number.cpp
	g++ -std=gnu++11 -c number.cpp
atom.o: atom.h atom.cpp
	g++ -std=gnu++11 -c atom.cpp
variable.o: variable.h variable.cpp
	g++ -std=gnu++11 -c variable.cpp
#Atom.o: Atom.h Atom.cpp
#	g++ -std=c++11 -c Atom.cpp

clean:
	rm -f *.o *hw2
stat:
	wc *.h *.cpp
