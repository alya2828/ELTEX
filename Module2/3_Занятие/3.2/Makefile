
CC = gcc

all: clean IP build

IP: IP.o
	$(CC) IP.o -o ./IP.out

IP.o: 
	$(CC) -c IP.c

build: 
	./IP.out

clean: 
	rm -rf *.o