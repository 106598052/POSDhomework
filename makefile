all: hw8 shell

hw8: main.o atom.o list.o struct.o exp.h
ifeq (${OS}, Windows_NT)
	g++ -o hw8 main.o atom.o list.o struct.o -lgtest
else
	g++ -o hw8 main.o atom.o list.o struct.o -lgtest -lpthread
endif

shell: shell.o atom.o struct.o list.o parser.h scanner.h exp.h atom.h variable.h iterator.h
ifeq (${OS}, Windows_NT)
	g++ -o shell shell.o struct.o list.o atom.o -lgtest
else
	g++ -o shell shell.o struct.o list.o atom.o -lgtest -lpthread
endif

shell.o:  shell.cpp atom.h variable.h struct.h iterator.h global.h list.h scanner.h parser.h struct.o list.o atom.o
	g++ -std=gnu++0x -c shell.cpp

main.o: main.cpp
	g++ -std=gnu++11 -c main.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++11 -c atom.cpp

list.o:list.cpp list.h
	g++ -std=gnu++11 -c list.cpp

struct.o:struct.cpp struct.h
	g++ -std=gnu++11 -c struct.cpp

clean:
	rm -f *.o hw8 shell
stat:
	wc *.h *.cpp
