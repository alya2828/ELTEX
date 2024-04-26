CC = gcc
AR = ar rcs
CFLAGS = -Wall
LDFLAGS = -L. -lcontacts

all: contacts.o libcontacts.a program build
# Компилируем contacts.c в объектный файл contacts.o
contacts.o: contacts.c contacts.h
	$(CC) $(CFLAGS) -c contacts.c

# Создаем статическую библиотеку libcontacts.a из объектного файла contacts.o
libcontacts.a: contacts.o
	$(AR) libcontacts.a contacts.o

# Компилируем main.c и связываем с библиотекой libcontacts.a
program: main.c libcontacts.a
	$(CC) $(CFLAGS) main.c -o program $(LDFLAGS)
build: 
	./program

# Очистка
clean:
	rm -f contacts.o libcontacts.a program
