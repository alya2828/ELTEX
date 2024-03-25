
CC = gcc

all: calculation2 build

calculation2: calculation2.o
	$(CC) calculation2.o -o ./calculation2.out

calculation2.o: 
	$(CC) -c calculation2.c

build: 
	./calculation2.out

clean: 
	rm -rf *.o