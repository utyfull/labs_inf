#ifndef _SEMANTIC_ANALIZER_H_
#define _SEMANTIC_ANALIZER_H_

#include "../sintaxAnalizer/sintaxAnalizer.h"

typedef struct
{
    ASTNode *queue[10];
} nodeQueue;

typedef struct
{
    tokenType type;
    int priority;
} keyWordPriority;

void makeQueue(ASTNode *root);
void checkSemantic(nodeQueue NodeQueue);

#endif