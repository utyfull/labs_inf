#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>

typedef struct Node
{
    size_t data; // Машинное слово
    struct Node *next;
} Node;

Node *createNode(size_t data);
void append(Node **head, size_t data);
void swapHalves(Node **head);
void printList(Node *head);
int listLength(Node *head);
void clearList(Node **head);
Node *deleteValue(Node **head, size_t value);
void insertAtIndex(Node **head, Node *value, int index);

#endif