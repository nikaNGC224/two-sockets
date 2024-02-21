.PHONY: all clean

all: run

clean:
	rm -rf run *.o

run: main.o buffer.o functions.o
	g++ main.o buffer.o functions.o -o run -lpthread

main.o: main.cpp
	g++ -c main.cpp -lpthread

buffer.o: buffer.cpp
	g++ -c buffer.cpp -lpthread

functions.o: functions.cpp
	g++ -c functions.cpp -lpthread
