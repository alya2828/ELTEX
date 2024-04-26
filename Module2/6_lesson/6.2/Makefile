# Названия файлов
CONTACTS_SRC = contacts.c
CONTACTS_OBJ = contacts.o
LIB_NAME = libcontacts.so
MAIN_SRC = main.c
MAIN_OBJ = main.o
PROGRAM = program

# Флаги компиляции
CFLAGS = -fPIC
LDFLAGS = -shared
LDLIBS = -lcontacts

# Правила компиляции
all: $(PROGRAM) build

# Компиляция объектного файла из исходного кода контактов
$(CONTACTS_OBJ):
	gcc $(CFLAGS) -c $(CONTACTS_SRC)

# Компиляция динамической библиотеки
$(LIB_NAME): $(CONTACTS_OBJ)
	gcc $(LDFLAGS) -o $(LIB_NAME) $(CONTACTS_OBJ)

# Компиляция объектного файла из исходного кода main
$(MAIN_OBJ):
	gcc $(CFLAGS) -c $(MAIN_SRC)

# Компиляция программы с использованием библиотеки
$(PROGRAM): $(MAIN_OBJ) $(LIB_NAME)
	gcc -o $(PROGRAM) $(MAIN_OBJ) -L. $(LDLIBS) 
#-Wl,-rpath,.

build: 
	./program

# Очистка сгенерированных файлов
clean:
	rm -f $(PROGRAM) $(CONTACTS_OBJ) $(LIB_NAME) $(MAIN_OBJ)