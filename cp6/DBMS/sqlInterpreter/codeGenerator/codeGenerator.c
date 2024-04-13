
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
        "SELECT PlanetName, openingYear FROM table_name WHERE PlanetName < 5 AND PlanetName > 4;";
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
    int pos = 0;
    columnList Columns;

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
                    pos++;
                }
            }
            if (pos != Queue->queueSize)
            {
                fprintf(stderr, "TOO MANY ARGUMENTS FOR INSERT");
                exit(EXIT_FAILURE);
            }
        }
        else if (Queue->queue[pos]->type == FROM)
        {
            readTableFromFile("WTF.db", &Table);
            pos++;
        }
        else if (Queue->queue[pos]->type == SELECT)
        {
            if (Table == NULL)
            {
                fprintf(stderr, "NEED TABLE FOR SELECT");
            }
            else
            {
                if (Queue->queue[pos]->children[0]->type == ALL)
                {
                    for (int i = 0; i < Table->size; i++)
                    {
                        Columns.id[Columns.size++] = i;
                    }
                    pos++;
                }
                else
                {
                    for (int i = 0; i < Table->size; i++)
                    {
                        for (int j = 0; j < Queue->queue[pos]->numChildren; j++)
                        {
                            if (strcmp(Table->columns[i]->columnName, Queue->queue[pos]->children[j]->lexeme) == 0)
                            {
                                Columns.id[Columns.size] = i;
                            }
                        }
                    }
                    pos++;
                }
            }
            if (pos == Queue->queueSize)
            {
                for (int i = 0; i < Columns.size; i++)
                {
                    printColumn(Table->columns[Columns.id[i]]);
                }
            }
            else
            {
                if (Queue->queue[pos]->type != WHERE)
                {
                    fprintf(stderr, "NEED WHERE AFTER FROM");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (Queue->queue[pos]->type == WHERE)
        {
            int max = 0;
            stringInd *list = NULL;
            if (Queue->queue[pos]->numChildren % 3 != 0 || Queue->queue[pos]->numChildren % 4 != 0)
            {
                fprintf(stderr, "TOO SMALL ARGIMENTS FOR WHERE");
                exit(EXIT_FAILURE);
            }
            if (Queue->queue[pos]->numChildren)

                while (max < Queue->queue[pos]->numChildren)
                {

                    if (Queue->queue[pos]->children[max]->type == AND)
                    {
                    }
                }
            if (pos != Queue->queueSize)
            {
                fprintf(stderr, "NEED NOTHING AFTER WHERE");
                exit(EXIT_FAILURE);
            }
        }
    }
}

stringInd *makeSearchC(stringInd *list, column *column1, column *column2, tokenType operator)
{
    stringInd *temp = malloc(sizeof(stringInd));

    if (column1->type != column2->type)
    {
        fprintf(stderr, "WRONG TYPES");
        exit(EXIT_FAILURE);
    }

    if (operator== EQUAL_TO)
    {
        for (int i = 0; i < column1->size; i++)
        {
            if (column1->Cells[i]->data == column2->Cells[i]->data)
            {
                if (list != NULL)
                {
                    for (int j = 0; j < list->size; j++)
                    {
                        if (list->ind[j] == i)
                        {
                            temp->ind[temp->size++] = i;
                        }
                    }
                }
                else
                {
                    temp->ind[temp->size++] = i;
                }
            }
        }
    }
    else if (operator== GREATER_THAN)
    {
        for (int i = 0; i < column1->size; i++)
        {
            if (*(float *)column1->Cells[i]->data > *(float *)column2->Cells[i]->data)
            {
                if (list != NULL)
                {
                    for (int j = 0; j < list->size; j++)
                    {
                        if (list->ind[j] == i)
                        {
                            temp->ind[temp->size++] = i;
                        }
                    }
                }
                else
                {
                    temp->ind[temp->size++] = i;
                }
            }
        }
    }
    else if (operator== LESS_THAN)
    {
        for (int i = 0; i < column1->size; i++)
        {
            if (*(float *)column1->Cells[i]->data < *(float *)column2->Cells[i]->data)
            {
                if (list != NULL)
                {
                    for (int j = 0; j < list->size; j++)
                    {
                        if (list->ind[j] == i)
                        {
                            temp->ind[temp->size++] = i;
                        }
                    }
                }
                else
                {
                    temp->ind[temp->size++] = i;
                }
            }
        }
    }
    else
    {
        fprintf(stderr, "WRONG OPERATOR");
        exit(EXIT_FAILURE);
    }
    return temp;
}

stringInd *makeSearchV(stringInd *list, column *column1, void *value, tokenType operator)
{
    stringInd *temp = malloc(sizeof(stringInd));

    // if (column1->type != column2->type)
    // {
    //     fprintf(stderr, "WRONG TYPES");
    //     exit(EXIT_FAILURE);
    // }

    if (operator== EQUAL_TO)
    {
        for (int i = 0; i < column1->size; i++)
        {
            if (*(float *)column1->Cells[i]->data == *(float *)value)
            {
                if (list != NULL)
                {
                    for (int j = 0; j < list->size; j++)
                    {
                        if (list->ind[j] == i)
                        {
                            temp->ind[temp->size++] = i;
                        }
                    }
                }
                else
                {
                    temp->ind[temp->size++] = i;
                }
            }
        }
    }
    else if (operator== GREATER_THAN)
    {
        for (int i = 0; i < column1->size; i++)
        {
            if (*(float *)column1->Cells[i]->data > *(float *)value)
            {
                if (list != NULL)
                {
                    for (int j = 0; j < list->size; j++)
                    {
                        if (list->ind[j] == i)
                        {
                            temp->ind[temp->size++] = i;
                        }
                    }
                }
                else
                {
                    temp->ind[temp->size++] = i;
                }
            }
        }
    }
    else if (operator== LESS_THAN)
    {
        for (int i = 0; i < column1->size; i++)
        {
            if (*(float *)column1->Cells[i]->data < *(float *)value)
            {
                if (list != NULL)
                {
                    for (int j = 0; j < list->size; j++)
                    {
                        if (list->ind[j] == i)
                        {
                            temp->ind[temp->size++] = i;
                        }
                    }
                }
                else
                {
                    temp->ind[temp->size++] = i;
                }
            }
        }
    }
    else
    {
        fprintf(stderr, "WRONG OPERATOR");
        exit(EXIT_FAILURE);
    }
    return temp;
}