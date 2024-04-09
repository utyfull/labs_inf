#ifndef _SINTAX_ANALIZER_H_
#define _SINTAX_ANALIZER_H_

#include "../lexicalAnalizer/lexicalAnalizer.h"

typedef struct ASTNode ASTNode;

typedef struct ASTNode
{
    tokenType type;
    char lexeme[100];
    ASTNode *children[20];
    int numChildren;
} ASTNode;

ASTNode *createASTNode(tokenType type, const char *lexeme);
void freeAST(ASTNode **root);
ASTNode *parse(token *tokenList, int numTokens);
void printASTNode(ASTNode *node, int depth);

#endif