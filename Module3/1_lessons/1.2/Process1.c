#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

long square(long lenght)
{
    return lenght * lenght;
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int rv;
    pid = fork();

    switch (pid)
    {
    case -1:
        perror(" Ошибка при вызове fork");
        exit(EXIT_FAILURE);
    case 0:
        printf("Дочерний процесс:\n");
        for (int i = 1; i <= argc / 2; i++)
        {
            long lenght = atol(argv[i]);
            long result = square(lenght);
            printf("Площадь стороны %s = %ld\n", argv[i], result);
        }
        exit(EXIT_SUCCESS);
    default:
        wait(&rv);
        printf("Родительский процесс:\n");
        for (int i = argc / 2 + 1; i < argc; i++)
        {
            long lenght = atol(argv[i]);
            long result = square(lenght);
            printf("Площадь стороны %s = %ld\n", argv[i], result);
        }

       
    }
     exit(EXIT_SUCCESS);
}
