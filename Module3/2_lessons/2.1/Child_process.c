#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_values>\n", argv[0]);
        return 1;
    }
    
    int num_values = atoi(argv[1]);  
    int pipefd[2];
    pid_t pid;
    
    pipe(pipefd);
    
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
 
        close(pipefd[0]);  
        
        srand(getpid());  
        
        
        int count = 0;
        while (count < num_values) {
            int random_num = rand() % 100;  
            write(pipefd[1], &random_num, sizeof(random_num));  // Пишем число в pipe
            count++;  
        }
        
        close(pipefd[1]);  // Закрываем конец для записи
    } else {
        
        close(pipefd[1]);  // Закрываем конец для записи
        
        // Открываем файл для записи
        FILE *output_file = fopen("output.txt", "w");
        if (output_file == NULL) {
            perror("fopen");
            return 1;
        }
        
        int received_num;
        int bytes_read;
        
        // Чтение значений из pipe и запись в файл
        while ((bytes_read = read(pipefd[0], &received_num, sizeof(received_num))) > 0) {
            if (bytes_read != sizeof(received_num)) {
                fprintf(stderr, "Ошибка: прочитано неправильное количество байтов.\n");
                fclose(output_file);
                close(pipefd[0]);
                return 1;
            }
            
            printf("%d\n", received_num); 
            fprintf(output_file, "%d\n", received_num); 
        }
        
        fclose(output_file);
        close(pipefd[0]);  
    }

    return 0;
}
