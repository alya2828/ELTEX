# Названия файлов
CONTACTS_SRC = contacts.c
CONTACTS_OBJ = contacts.o
LIB_NAME = libcontacts.so
MAIN_SRC = main.c
MAIN_OBJ = main.o
PROGRAM = program

# Флаги компиляции
CFLAGS = -Wall
LDFLAGS = -shared
LDLIBS = -lcontacts

# Правила компиляции
all: build run
	
run:
	./program

build: compile_library
	gcc $(CFLAGS) -c main.c
	gcc main.o -L. -lcontacts -o program -Wl,-rpath,.

compile_library: compile
	gcc -shared -o libcontacts.so contacts.o
compile:
	gcc $(CFLAGS) -fPIC -c contacts.c
# Очистка сгенерированных файлов
clean:
	rm -f *.so *.o program
	
