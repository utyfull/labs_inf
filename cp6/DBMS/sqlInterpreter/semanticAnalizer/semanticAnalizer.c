
#include "semanticAnalizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const keyWordPriority keyPriority[] = {
    {TABLE_DDL, 1},
    {CREATE, 2},
    {ALTER, 3},
    {DROP, 4},
    {SELECT, 9},
    {INSERT, 6},
    {UPDATE, 7},
    {DELETE, 8},
    {FROM, 5},
    {JOIN, 10},
    {ON, 11},
    {WHERE, 12},
    {GROUPBY, 13},
    {HAVING, 14},
    {ORDERBY, 15},
    {LIMIT, 16},
    {INTO, 17},
    {VALUES, 18},
    {VALUES_LIST, 19},
    {SET, 20}};

void printQueue(nodeQueue *nodeQueue)
{
    for (int i = 0; i < nodeQueue->queueSize; i++)
    {
        printASTNode(nodeQueue->queue[i], 0);
        printf("%d - priority\n", nodeQueue->queue[i]->priority);
        printf("%d - position\n", nodeQueue->queue[i]->position);
    }
}

ASTNode *checkPriority(ASTNode *node)
{
    ASTNode *temp = malloc(sizeof(ASTNode));
    temp->type = node->type;
    strcpy(temp->lexeme, node->lexeme);
    temp->numChildren = 0;

    for (int i = 0; i < node->numChildren; i++)
    {
        if (node->children[i]->numChildren == 0)
        {
            temp->children[temp->numChildren++] = node->children[i];
        }
    }

    if (temp->numChildren == 0)
    {
    }
    for (int i = 0; i < NUM_KEYPRIORITY; i++)
    {
        if (temp->type == keyPriority[i].type)
        {
            temp->priority = keyPriority[i].priority;
            return temp;
        }
    }
    if (temp->numChildren != 0)
    {
        fprintf(stderr, "ERROR: WRONG KEYWORD");
        exit(EXIT_FAILURE);
    }
    else
    {
        return temp;
    }
}
void recursivSearch(ASTNode *node, nodeQueue **Queue)
{
    for (int i = 0; i < node->numChildren; i++)
    {
        if (node->children[i]->numChildren != 0)
        {
            (*Queue)->queue[(*Queue)->queueSize++] = checkPriority(node->children[i]);

            recursivSearch(node->children[i], Queue);
        }
    }
}

nodeQueue *makeQueue(ASTNode *root)
{
    nodeQueue *currentQueue = (nodeQueue *)malloc(sizeof(nodeQueue));
    currentQueue->queueSize = 0;

    recursivSearch(root, &currentQueue);
    for (int i = 0; i < currentQueue->queueSize; i++)
    {
        currentQueue->queue[i]->position = i;
    }
    return currentQueue;
}

void deleteQueue(nodeQueue **Queue)
{
    for (int i = 0; i < ((*Queue)->queueSize); i++)
    {
        freeAST(&(*Queue)->queue[i]);
    }
    free((*Queue)->queue);
}

int main()
{
    // Test Lexer
    //-------------
    // Test Sintaxer
    //-------------
    // Test sematic analizer
    token *tokenList = malloc(sizeof(token) * 20);
    char *input =
        "CREATE TABLE table_name (column1 INT, column2 CHAR);";

    lexer *Lexer = createLexer(input);
    int i = 0;
    while (Lexer->position < strlen(Lexer->input))
    {
        tokenList[i] = getNextToken(&Lexer);
        printf("%s - value, %d - type\n", tokenList[i].lexeme, tokenList[i].type);
        i++;
    }
    printf("-----------------------\n");
    int tokenLen = i;
    // Test parser
    ASTNode *root = parse(tokenList, tokenLen);
    printASTNode(root, 0);
    printf("---------------------------\n");
    nodeQueue *queue = makeQueue(root);
    printQueue(queue);
    destroyLexer(&Lexer);
    freeAST(&root);
    free(queue);
}