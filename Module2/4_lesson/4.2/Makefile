CC = gcc
CFLAGS = -Wall -Wextra

all: Queue build

Process3: Queue.c
	$(CC) $(CFLAGS) -o Queue Queue.c
	
build:
	./Queue

clean:
	rm -f Queue