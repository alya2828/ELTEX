CC = gcc
CFLAGS = -Wall -Wextra

all: Process1 Process2

Process1:
	$(CC) $(CFLAGS) -o Process1 ../1.2/Process1.c


Process2: Process2.c
	$(CC) $(CFLAGS) -o Process2 Process2.c

clean:
	rm -f Process2 Process1
