CC = gcc

all: calculation plus.so minus.so division.so multiplication.so build clean

plus.so:
	$(CC)  -shared -o plus.so plus.c

minus.so:
	$(CC) -shared -o minus.so minus.c

division.so:
	$(CC)  -shared -o division.so division.c

multiplication.so:
	$(CC) -shared -o multiplication.so multiplication.c

calculation:
	$(CC)  -o calculation calculation.c -ldl

build:
	./calculation
clean:
	rm -f calculation plus.so minus.so division.so multiplication.so