#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h> 
#include <unistd.h> 

#define MAX_LENGTH 256

struct msgbuf   
{
    long mtype;
    char mtext[MAX_LENGTH];
};

int main()
{
    key_t key;
    int msg_id;
    struct msgbuf message;

    // Получаем ключ 
    key = ftok("1.txt", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Создание очереди
    msg_id = msgget(key, IPC_CREAT | 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(1);
    }

    srand(time(NULL));

   while (1)
{
    int random_number = rand() % 256;
    sprintf(message.mtext, "%d", random_number);
    message.mtype = 1;

    // Отправка сообщения в очередь
    if (msgsnd(msg_id, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    
    // Проверка на завершение обмена данными
    if (random_number == 255) {
        strcpy(message.mtext, "Завершение обмена");
        message.mtype = 255;
        if (msgsnd(msg_id, &message, sizeof(message.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        sleep(1); 
        break; // Выход из цикла после отправки сообщения с числом 255
    }
}
}