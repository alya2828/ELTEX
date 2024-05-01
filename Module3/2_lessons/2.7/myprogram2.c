#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Функция-обработчик сигналов
void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("Received SIGINT signal\n");
    }
    else if (signum == SIGQUIT)
    {
        printf("Received SIGQUIT signal\n");
    }
}

int main()
{
    // Устанавливаем обработчик сигналов SIGINT и SIGQUIT
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

  
    FILE *file = fopen("file.txt", "a");
    if (file == NULL)
    {
        perror("Failed to open file");
        return 1;
    }
    int counter = 1;
    while (1)
    {
        fprintf(file, "%d\n", counter);
        counter++;
        sleep(1);
    }
    return 0;
}