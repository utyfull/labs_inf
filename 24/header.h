#ifndef __HEAD_H_
#define __HEAD_H_

typedef struct Node
{
    char data[100];
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char *data);
Node *buildTree(char *str, char *sep);
void printTree(Node *root);
void freeRoot(Node *root);
void makeSumSquare(Node *root);
void checkOperators(Node *root);
int toSqrt(int num);

#endif