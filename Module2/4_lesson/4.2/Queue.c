#include "Queue.h"


Node* createNode(int data, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}


PriorityQueue* initializeQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    pq->rear = NULL;
    return pq;
}

void enqueue(PriorityQueue* pq, int data, int priority) {
    Node* newNode = createNode(data, priority);

    
    if (pq->front == NULL || priority > pq->front->priority) {
        newNode->next = pq->front;
        if (pq->front != NULL)
            pq->front->prev = newNode;
        pq->front = newNode;
        if (pq->rear == NULL)
            pq->rear = newNode;
    } else {
        Node* current = pq->front;
        // Находим место для вставки элемента
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        if (current->next != NULL)
            current->next->prev = newNode;
        current->next = newNode;
        newNode->prev = current;
    }
}

// Извлечение элемента с наивысшим приоритетом из очереди
int dequeue(PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Очередь пуста\n");
        return -1; 
    }

    int data = pq->front->data;
    Node* temp = pq->front;
    pq->front = pq->front->next;
    if (pq->front != NULL)
        pq->front->prev = NULL;
    free(temp);

    if (pq->front == NULL)
        pq->rear = NULL;

    return data;
}


void clearQueue(PriorityQueue* pq) {
    while (pq->front != NULL) {
        Node* temp = pq->front;
        pq->front = pq->front->next;
        free(temp);
    }
    pq->rear = NULL;
}

void generateMessages(PriorityQueue* pq, int numMessages) {
    srand(time(NULL)); 
    for (int i = 0; i < numMessages; ++i) {
        int data = rand() % 100; 
        int priority = rand() % 10; 
        
        enqueue(pq, data, priority);
    }
}

// Выборка данных с определенным приоритетом из очереди
void MessagesWithPriority(PriorityQueue* pq, int priority) {
    printf("Извлечение сообщений с приоритетом %d:\n", priority);
    while (pq->front != NULL && pq->front->priority == priority) {
        int data = dequeue(pq);
        printf("Данные: %d\n", data);
    }
}

// Выборка данных с приоритетом не менее указанного из очереди
void MessagesWithMinPriority(PriorityQueue* pq, int minPriority) {
    printf("Извлечение сообщений с приоритетом не менее %d:\n", minPriority);
    while (pq->front != NULL && pq->front->priority >= minPriority) {
        int data = dequeue(pq);
        printf("Данные: %d\n", data);
    }
}

int main() {
    PriorityQueue* pq = initializeQueue();

    
    generateMessages(pq, 20); 
   
    MessagesWithPriority(pq, 0); 
    MessagesWithMinPriority(pq, 3); 
    clearQueue(pq);
    free(pq);

    return 0;
}