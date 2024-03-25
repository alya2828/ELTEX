
CC = gcc

all: calculation build

calculation: calculation.o
	$(CC) calculation.o -o ./calculation.out

calculation.o: 
	$(CC) -c calculation.c

build: 
	./calculation.out

clean: 
	rm -rf *.o