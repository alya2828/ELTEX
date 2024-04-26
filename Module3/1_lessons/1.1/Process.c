#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void exit_handler()
{
    printf("Программа завершила свою работу.\n");
}

int main(int argc, char *argv[])
{
    // Установка обработчика сигнала завершения
    atexit(exit_handler);
    pid_t pid;
    int rv;
    // Создание дочернего процесса
    pid = fork();

    switch (pid)
    {
    case -1:
        perror(" Ошибка при вызове fork");
        exit(EXIT_FAILURE);
    case 0:
        // Это дочерний процесс
        printf("Дочерний процесс:\n");
        for (int i = 0; i < argc; i++)
        {
            printf("Аргумент %d: %s\n", i, argv[i]);
        }

        exit(EXIT_SUCCESS);
    default:
        wait(&rv);
        printf("Родительский процесс:\n");
        for (int i = 0; i < argc; i++)
        {
            printf("Аргумент %d: %s\n", i, argv[i]);
        }

        exit(EXIT_SUCCESS);
    }
}