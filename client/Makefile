.PHONY: all clean

all: run

clean:
	rm -rf run *.o

run: main.o
	g++ main.o -o run

main.o: main.cpp
	g++ -c main.cpp
