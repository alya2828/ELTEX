#include <stdio.h>
#include <unistd.h>
#include <signal.h>

FILE *file;
int counter = 1;
int sigint_count = 0;  
// Обработчик сигналов SIGINT
void sigint_handler(int sig)
{
    sigint_count++;  

    if (sigint_count >= 3)  
    {
        fclose(file);  
        printf("\nReceived 3 SIGINT signals. Exiting...\n");
        _exit(0);  
    }
}

int main()
{   signal(SIGINT, sigint_handler);

    file = fopen("file.txt", "a");
    if (file == NULL)
    {
        perror("Failed to open file");
        return 1;
    }

    while (1)
    {
        fprintf(file, "%d\n", counter);
        counter++;
        sleep(1);
    }

    
    fclose(file);
    return 0;
}
