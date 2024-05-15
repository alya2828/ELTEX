CC = gcc
CFLAGS = -Wall -Wextra

all: myprogram myprogram1

myprogram: myprogram.c
	$(CC) $(CFLAGS) -o myprogram myprogram.c

myprogram1: myprogram1.c
	$(CC) $(CFLAGS) -o myprogram1 myprogram1.c

run_myprogram: myprogram
	./myprogram

run_myprogram1: myprogram1
	./myprogram1

clean:
	rm -f myprogram myprogram1