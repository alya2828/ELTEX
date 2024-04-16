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

#endif 
