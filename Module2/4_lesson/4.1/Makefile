
CC = gcc

all: clean contacts build

contacts: contacts.o
	$(CC) contacts.o -o ./contacts.out

contacts.o: 
	$(CC) -c contacts.c

build: 
	./contacts.out

clean: 
	rm -rf *.o
