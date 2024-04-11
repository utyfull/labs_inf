#ifndef _SEMANTIC_ANALIZER_H_
#define _SEMANTIC_ANALIZER_H_

#include "../sintaxAnalizer/sintaxAnalizer.h"

#define NUM_KEYPRIORITY 20

typedef struct
{
    ASTNode *queue[20];
    int queueSize;
} nodeQueue;

typedef struct
{
    tokenType type;
    int priority;
} keyWordPriority;

extern const keyWordPriority keyPriority[];

void deleteQueue(nodeQueue **Queue);
void printQueue(nodeQueue *nodeQueue);
void recursivSearch(ASTNode *node, nodeQueue **Queue);
ASTNode *checkPriority(ASTNode *node);
nodeQueue *makeQueue(ASTNode *root);
void checkSemantic(nodeQueue *nodeQueue);

#endif