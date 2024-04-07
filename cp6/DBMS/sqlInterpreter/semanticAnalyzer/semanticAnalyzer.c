
#include "semanticAnalyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ASTNode* createASTNode(tokenType type, const char* lexeme) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) {
        fprinf(stderr, "ERROR MEMORY ALLOC");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    strncpy(node->lexeme, lexeme, 100 - 1);
    node->lexeme[100 - 1] = '\0';
    node->numChildren = 0;
    return node;
}


void freeAST(ASTNode** root) {
    if (root == NULL)
        return;
    for (int i = 0; i < (*root)->numChildren; i++) 
        freeAST((*root)->children[i]);
    free(root);
}

ASTNode* parse(token* tokenList, int numTokens) {

    // AST root
    ASTNode* root = createASTNode(QUERY, "query");
    int currentTokenIndex = 0;


    // Parce main structure
    while (currentTokenIndex < numTokens) {
        token currentToken = tokenList[currentTokenIndex];


        // If SELECT
        if (currentToken.type == SELECT) {
            ASTNode* selectNode = createASTNode(SELECT, "SELECT");
            // Add to root

            root->children[root->numChildren++] = selectNode;
            currentTokenIndex++;


            // Column list
            while (currentTokenIndex < numTokens && tokenList[currentTokenIndex].type != FROM) {
                ASTNode* columnNode = createASTNode(COLUMN, tokenList[currentTokenIndex].lexeme);
                selectNode->children[selectNode->numChildren++] = columnNode;
                currentTokenIndex++;
            }
            continue;

        // If FROM
        } else if (currentToken.type == FROM) {
            ASTNode* fromNode = createASTNode(FROM, "FROM");

            root->children[root->numChildren++] = fromNode;
            currentTokenIndex++;

            //Table list
            while (currentTokenIndex < numTokens && tokenList[currentTokenIndex].type != WHERE) {

                ASTNode* tableNode = createASTNode(TABLE, tokenList[currentTokenIndex].lexeme);
                fromNode->children[fromNode->numChildren++] = tableNode;

                currentTokenIndex++;
            }
            continue;

        // If Where
        } else if (currentToken.type == WHERE) {
            ASTNode* whereNode = createASTNode(WHERE, "WHERE");

            root->children[root->numChildren++] = whereNode;

            currentTokenIndex++;

            while (currentTokenIndex < numTokens) {
                token currentToken = tokenList[currentTokenIndex];

                // If operator (<, == , != i t. d.)
                for (int i = 0; i < NUM_OPERATORS; i++) {
                    if (strcmp(currentToken.type, (tokenType)operatorsList[i]) == 0) {
                        ASTNode* compressionNode = createASTNode((tokenType)operatorsList[i], currentToken.lexeme);
                        whereNode->children[whereNode->numChildren++] = compressionNode;

                        currentTokenIndex++;
                    }
                }

                // If logical operator (AND, OR, NOT)
                if (currentToken.type == AND || currentToken.type == OR || currentToken.type == NOT) {
                    
                    ASTNode* logicalNode = createASTNode(currentToken.type, currentToken.lexeme);
                    whereNode->children[whereNode->numChildren++] = logicalNode;

                    currentTokenIndex++;
                }

                // If identifier or value
                else if (currentToken.type == IDENTIFIER || currentToken.type == NUMBER || currentToken.type == STRING) {

                    ASTNode* wtfNode = createASTNode(currentToken.type, currentToken.lexeme);
                    whereNode->children[whereNode->numChildren - 1]->children[1] = wtfNode;

                    currentTokenIndex++;

                }

            }
            continue;



        }
        
        
        
        
        else {
            // Errors
            fprintf(stderr, "ERROR: WRONG TOKEN: %s\n", currentToken.lexeme);
            exit(EXIT_FAILURE);
        }
    }

    return root;

}