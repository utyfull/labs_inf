#ifndef __HEAD_H_
#define __HEAD_H_

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char data);
Node *buildTree(char *str, int *index);
void printTree(Node *root);

#endif