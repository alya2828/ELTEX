#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 256

struct msgbuf {
    long mtype;
    char mtext[MAX_LENGTH];
};

int main() {
    key_t key;
    int msg_id;
    struct msgbuf message;
    key = ftok("1.txt", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    msg_id = msgget(key, 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        if (msgrcv(msg_id, &message, sizeof(message.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        int received_number = atoi(message.mtext);

        if (received_number == 255) {
            printf("Программа завершила работу.\n");
            break;
        }
        printf("Получено число: %d\n", received_number);
    }

    return 0;
}