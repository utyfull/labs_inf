#ifndef _HEADER_H_
#define _HEADER_H_

typedef struct Node {
    int data; // Машинное слово
    struct Node* next;
} Node;

Node* createNode(int data);
void append(Node** head, int data);
void swapHalves(Node** head);
void printList(Node* head);


#endif