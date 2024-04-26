#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 10
#define MAX_LENGTH 100

int main() {
    char input[MAX_LENGTH];
    char *args[MAX_ARGS];
    int num_args = 0;
    int rv;   
        printf("Введите команду: ");
        fgets(input, sizeof(input), stdin);
        
        
        char *token = strtok(input, " ");
        while (token != NULL && num_args < MAX_ARGS - 1) {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }
        args[num_args] = NULL;


        pid_t pid = fork();
        switch (pid)
    {
    case -1:
        
            perror("Ошибка при вызове fork");
            exit(EXIT_FAILURE);
       case 0:
            char path[MAX_LENGTH];
        snprintf(path, sizeof(path), "/home/alina/Документы/ELTEX/Module3/1_lessons/1.3/Process1");
        execv(path, args);
            perror("Ошибка при выполнении команды");
            exit(EXIT_FAILURE);
       case 1:
          
            wait(&rv);
            printf("Дочерний процесс завершил выполнение с кодом %d.\n", WEXITSTATUS(rv));
            exit(EXIT_SUCCESS);  
      }
     return 0;
    }