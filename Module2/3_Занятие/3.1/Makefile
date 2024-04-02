
CC = gcc

all: clean Chmod build

Chmod: Chmod.o
	$(CC) Chmod.o -o ./Chmod.out

Chmod.o: 
	$(CC) -c Chmod.c

build: 
	./Chmod.out

clean: 
	rm -rf *.o