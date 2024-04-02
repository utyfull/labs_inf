#ifndef _UDT_H_
#define _UDT_H_

// Node structure to represent each element in the linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* insertEnd(Node* head, int data);
void bubbleSort(Node* head);
void printList(Node* head);
void freeList(Node* head);
Node* createNode(int data);


#endif