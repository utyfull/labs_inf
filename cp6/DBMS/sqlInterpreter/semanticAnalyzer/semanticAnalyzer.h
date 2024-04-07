#ifndef _SEMANTIC_ANALYZER_H_
#define _SEMANTIC_ANALYZER_H_

#include "../lexicalAnalyzer/lexicalAnalizer.h"

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

#endif