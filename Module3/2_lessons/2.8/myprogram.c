#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t file_locked = 0;

void generate_numbers(char *filename, int num_values);
void signal_handler(int sig);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_values>\n", argv[0]);
        return 1;
    }
    int num_values = atoi(argv[1]);  
    char *filename = "file.txt";
    generate_numbers(filename, num_values);
    FILE *file = fopen(filename, "a+");
    if (file == NULL)
    {
        perror("Ошибка при открытии файла");
        return 1;
    }
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Ошибка при создании канала");
        fclose(file);
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    if (pid == 0)
    {
        // Дочерний процесс: читает из файла и отправляет числа родителю через канал
        close(pipe_fd[0]); // Закрываем неиспользуемый канал (для записи)

        int number;
        // Чтение чисел из файла
        while (fscanf(file, "%d", &number) != EOF)
        {
            printf("Дочерний процесс %d: прочитано число из файла: %d\n", getpid(), number);
            read(pipe_fd[1], &number, sizeof(number)); // Пишет в канал (родитель читает)
            kill(getppid(), SIGUSR2);                  // Сигнал родителю о том, что число прочитано
        }

        // После прочтения файла, дочерний процесс генерирует случайное число
        int new_number = rand() % 100;
        printf("Дочерний процесс %d: сгенерировано новое случайное число: %d\n", getpid(), new_number);

        // Отправка сгенерированного числа родительскому процессу через канал
        write(pipe_fd[1], &new_number, sizeof(new_number));
        kill(getppid(), SIGUSR2); // Сигнал родителю о том, что новое число готово

        close(pipe_fd[1]);
        fclose(file);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Parent pid = %d\n", getpid());
        close(pipe_fd[1]);
        int number;
        while (read(pipe_fd[0], &number, sizeof(number)) > 0)
        {
            printf("Родительский процесс %d: прочитано число из канала: %d\n", getpid(), number);
            printf("Блокирует перед изменением\n");
            kill(pid, SIGUSR1);
            waitpid(pid, NULL, 0);
            while (file_locked)
            {
            }
            fprintf(file, "%d\n", number);
            printf("Записывает число: %d в файл\n", number);
            printf("Разблокирует после изменения\n");
            kill(pid, SIGUSR2);
        }
        fclose(file);
        close(pipe_fd[0]);
        waitpid(pid, NULL, 0);
    }
}

void generate_numbers(char *filename, int num_values)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }
    srand(getpid());

    for (int i = 0; i < num_values; i++)
    {
        int number = rand() % 100;
        fprintf(file, "%d\n", number);
    }

    fclose(file);
}

void signal_handler(int sig)
{
    switch (sig)
    {
    case SIGUSR1:
        printf("Процесс %d: получен сигнал SIGUSR1 для блокировки\n", getpid());
        file_locked = 1;
        break;
    case SIGUSR2:
        printf("Процесс %d: получен сигнал SIGUSR2 для разблокировки\n", getpid());
        file_locked = 0;
        break;
    }
}