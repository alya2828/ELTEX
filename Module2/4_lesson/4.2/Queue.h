#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data; 
    int priority; 
    struct Node* next; 
    struct Node* prev;
} Node;


typedef struct {
    Node* front; 
    Node* rear; 
} PriorityQueue;

Node* createNode(int data, int priority);
PriorityQueue* initializeQueue();
void enqueue(PriorityQueue* pq, int data, int priority);
int dequeue(PriorityQueue* pq);
void clearQueue(PriorityQueue* pq);
void generateMessages(PriorityQueue* pq, int numMessages);
void MessagesWithPriority(PriorityQueue* pq, int priority);
void MessagesWithMinPriority(PriorityQueue* pq, int minPriority);

#endif 
