
#include "codeGenerator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typeRelation types[] = {{INT_T, INTEGER}, {CHAR_T, CHAR}, {FLOAT_T, FLOAT}};

int comparator(const void *p, const void *q)
{
    return (((ASTNode *)(p))->priority - ((ASTNode *)(q))->priority);
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
        "SELECT * FROM table;";
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

void generate(nodeQueue *Queue, table **TAble)
{
    table *Table = (*TAble);
    column *Column = NULL;
    int pos = 0;

    qsort((void *)Queue, Queue->queueSize, sizeof(*Queue), comparator);

    while (pos <= Queue->queueSize)
    {
        if (Queue->queue[pos]->type == CREATE)
        {
            if (Queue->queue[pos]->position != 0)
            {
                fprintf(stderr, "CREATE MUST BE IN 0 POSITION");
                exit(EXIT_FAILURE);
            }
            else
            {
                pos++;
                if (Queue->queue[pos]->type == TABLE_DDL)
                {
                    Table = createTable(Queue->queue[pos]->children[0]->lexeme, 0);
                    pos++;

                    if (Queue->queue[pos]->type == VALUES_LIST)
                    {
                        if (Queue->queue[pos]->numChildren % 2 != 0)
                        {
                            fprintf(stderr, "TOO SMALL ARGUMENTS");
                            exit(EXIT_FAILURE);
                        }
                        for (int i = 0; i < Queue->queue[pos]->numChildren; i++)
                        {
                            for (int i = 0; i < NUM_TYPES; i++)
                            {
                                if (Queue->queue[pos]->children[i + 1]->type == types[i].token)
                                    insertColumn(Queue->queue[pos]->children[i]->lexeme, &Table, types[i].type);
                                pos += 2;
                            }
                        }
                    }
                    if (pos != Queue->queueSize)
                    {
                        fprintf(stderr, "TOO MANY ARGUMENTS FOR CREATE");
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    fprintf(stderr, "POKA NET DRUGIH TIPOV DLYA CREATE");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (Queue->queue[pos]->type == INSERT)
        {
            if (Queue->queue[pos]->position != 0)
            {
                fprintf(stderr, "INSERT MUST BE IN 0 POSITION");
                exit(EXIT_FAILURE);
            }
            else
            {
                readTableFromFile("WTF.db", &Table);
                pos++;

                if (Queue->queue[pos]->type == COLUMN_LIST)
                {
                    if (Queue->queue[pos]->numChildren != Queue->queue[pos + 1]->numChildren)
                    {
                        fprintf(stderr, "COLUMN COUNT NOT EQUAL VALUES COUNT IN INSERT");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        for (int i = 0; i < Table->size; i++)
                        {
                            for (int j = 0; j < Queue->queue[pos]->numChildren; j++)
                            {
                                if (strcmp(Table->columns[i]->columnName, Queue->queue[pos]->children[j]->lexeme) == 0)
                                {
                                    insertValue(&Table, i, Queue->queue[pos + 1]->children[j]->lexeme);
                                }
                            }
                        }
                    }
                    pos += 2;
                }
                else
                {
                    if (Table->size != Queue->queue[pos]->numChildren)
                    {
                        fprintf(stderr, "COLUMN COUNT NOT EQUAL VALUES COUNT IN INSERT");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        for (int i = 0; i < Table->size; i++)
                        {
                            insertValue(&Table, i, Queue->queue[pos]->children[i]->lexeme);
                        }
                    }
                }
            }
            if (pos != Queue->queueSize)
            {
                fprintf(stderr, "TOO MANY ARGUMENTS FOR INSERT");
                exit(EXIT_FAILURE);
            }
        }
        // else if ()
        {
        }
    }
}