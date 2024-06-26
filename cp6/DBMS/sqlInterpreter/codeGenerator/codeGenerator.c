
#include "codeGenerator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typeRelation types[] = {{INT_T, INTEGER}, {CHAR_T, CHAR}, {FLOAT_T, FLOAT}};

void bubbleSort(nodeQueue **queue) // eto luchse zabit(za n^3 rabotaet, da ya geniy)(proclyatiy qsort v c ne rabotaet kak nado)
{
    ASTNode *temp;
    for (int i = 1; i < (*queue)->queueSize; i++)
    {
        if ((*queue)->queue[i - 1]->priority > (*queue)->queue[i]->priority)
        {
            temp = (*queue)->queue[i - 1];
            (*queue)->queue[i - 1] = (*queue)->queue[i];
            (*queue)->queue[i] = temp;
            if (i != (*queue)->queueSize)
            {
                bubbleSort(queue);
            }
        }
    }
}

int compar(const void *p, const void *q)
{
    if (((ASTNode *)(p))->priority < ((ASTNode *)(q))->priority)
    {
        return -1;
    }
    else if (((ASTNode *)(p))->priority > ((ASTNode *)(q))->priority)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int reverseCompar(const void *p, const void *q)
{
    if (((ASTNode *)(q))->priority < ((ASTNode *)(p))->priority)
    {
        return -1;
    }
    else if (((ASTNode *)(q))->priority > ((ASTNode *)(p))->priority)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void prepareGenerate(char *input, table **Table)
{
    // Test Lexer
    //-------------
    // Test Sintaxer
    //-------------
    // Test sematic analizer
    token *tokenList = malloc(sizeof(token) * 20);
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
    generate(queue, Table);
    destroyLexer(&Lexer);
    freeAST(&root);
    free(queue);
    queue = NULL;
}

column *searchColumnInd(table *Table, char *columnName)
{
    for (int i = 0; i < Table->size; i++)
    {
        if (strcmp(Table->columns[i]->columnName, columnName) == 0)
        {
            return Table->columns[i];
        }
    }
    return Table->columns[0];
}

void generate(nodeQueue *Queue, table **Table)
{
    int pos = 0;

    qsort(Queue, Queue->queueSize, sizeof(ASTNode *), compar);
    if (Queue->queueSize == 0)
    {
        return;
    }
    if (Queue->queue[0]->type == SELECT)
    {
        bubbleSort(&Queue);
    }
    // printf("%s\n", Queue->queue[0]->lexeme);
    // printf("%s\n", Queue->queue[1]->lexeme);
    // printf("%s\n", Queue->queue[2]->lexeme);
    // printf("%d\n", Queue->queue[0]->priority);
    // printf("%d\n", Queue->queue[1]->priority);
    // printf("%d\n", Queue->queue[2]->priority);

    while (pos < Queue->queueSize)
    {
        columnList Columns;
        if (Queue->queue[pos]->type == CREATE)
        {
            if (Queue->queue[pos]->position != 0)
            {
                fprintf(stderr, "CREATE MUST BE IN 0 POSITION\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                pos++;
                if (Queue->queue[pos]->type == TABLE_DDL)
                {
                    *Table = createTable(Queue->queue[pos]->children[0]->lexeme, 0);
                    pos++;

                    if (Queue->queue[pos]->type == VALUES_LIST)
                    {
                        if (Queue->queue[pos]->numChildren % 2 != 0)
                        {
                            fprintf(stderr, "TOO SMALL ARGUMENTS\n");
                            exit(EXIT_FAILURE);
                        }
                        for (int i = 0; i < Queue->queue[pos]->numChildren; i += 2)
                        {
                            for (int j = 0; j < NUM_TYPES; j++)
                            {
                                if (Queue->queue[pos]->children[i + 1]->type == types[j].token)
                                    insertColumn(Queue->queue[pos]->children[i]->lexeme, Table, types[j].type);
                            }
                        }
                        pos++;
                    }
                    if (pos != Queue->queueSize)
                    {
                        fprintf(stderr, "TOO MANY ARGUMENTS FOR CREATE\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    fprintf(stderr, "POKA NET DRUGIH TIPOV DLYA CREATE\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (Queue->queue[pos]->type == INSERT)
        {
            if (Queue->queue[pos]->position != 0)
            {
                fprintf(stderr, "INSERT MUST BE IN 0 POSITION\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                readTableFromFile("WTF.db", Table);
                pos++;

                if (Queue->queue[pos]->type == COLUMN_LIST)
                {
                    if (Queue->queue[pos]->numChildren != Queue->queue[pos + 1]->numChildren)
                    {
                        fprintf(stderr, "COLUMN COUNT NOT EQUAL VALUES COUNT IN INSERT\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        for (int i = 0; i < (*Table)->size; i++)
                        {
                            for (int j = 0; j < Queue->queue[pos]->numChildren; j++)
                            {
                                if (strcmp((*Table)->columns[i]->columnName, Queue->queue[pos]->children[j]->lexeme) == 0)
                                {

                                    insertValue(Table, i, Queue->queue[pos + 1]->children[j]->lexeme);
                                }
                            }
                        }
                    }
                    pos += 3;
                    continue;
                }
                else if (Queue->queue[pos]->type == VALUES_LIST)
                {
                    if ((*Table)->size != Queue->queue[pos]->numChildren)
                    {
                        fprintf(stderr, "COLUMN COUNT NOT EQUAL VALUES COUNT IN INSERT\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        for (int i = 0; i < (*Table)->size; i++)
                        {
                            insertValue(Table, i, Queue->queue[pos]->children[i]->lexeme);
                        }
                    }
                    pos += 2;
                    continue;
                }
            }
            if (pos != Queue->queueSize)
            {
                fprintf(stderr, "TOO MANY ARGUMENTS FOR INSERT\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (Queue->queue[pos]->type == FROM)
        {
            readTableFromFile("WTF.db", Table);
            pos++;
        }
        else if (Queue->queue[pos]->type == SELECT)
        {
            Columns.size = 0;
            if ((*Table) == NULL)
            {
                fprintf(stderr, "NEED TABLE FOR SELECT\n");
            }
            else
            {
                if (strcmp(Queue->queue[pos]->children[0]->lexeme, "*") == 0)
                {
                    for (int i = 0; i < (*Table)->size; i++)
                    {
                        Columns.id[Columns.size++] = i;
                    }
                    pos++;
                }
                else
                {
                    for (int i = 0; i < (*Table)->size; i++)
                    {
                        for (int j = 0; j < Queue->queue[pos]->numChildren; j++)
                        {
                            if (strcmp((*Table)->columns[i]->columnName, Queue->queue[pos]->children[j]->lexeme) == 0)
                            {
                                Columns.id[Columns.size++] = i;
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
                    printColumn((*Table)->columns[Columns.id[i]]);
                }
                break;
            }
            else
            {
                if (Queue->queue[pos]->type != WHERE)
                {
                    fprintf(stderr, "NEED WHERE AFTER FROM\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (Queue->queue[pos]->type == WHERE)
        {
            int max = 0;
            stringInd *list = NULL;
            if (Queue->queue[pos]->numChildren % 3 != 0 && Queue->queue[pos]->numChildren % 4 != 0)
            {
                fprintf(stderr, "TOO SMALL ARGIMENTS FOR WHERE\n");
                exit(EXIT_FAILURE);
            }
            if (Queue->queue[pos]->numChildren == 3)
            {
                if (Queue->queue[pos]->children[2]->type != IDENTIFIER)
                {
                    list = makeSearchV(list, searchColumnInd(*Table, Queue->queue[pos]->children[0]->lexeme), atof(Queue->queue[pos]->children[2]->lexeme), Queue->queue[pos]->children[1]->type);
                }
                else
                {
                    list = makeSearchC(list, searchColumnInd(*Table, Queue->queue[pos]->children[0]->lexeme), searchColumnInd(*Table, Queue->queue[pos]->children[2]->lexeme), Queue->queue[pos]->children[1]->type);
                }
            }
            else
            {

                while (max < Queue->queue[pos]->numChildren)
                {

                    if (Queue->queue[pos]->children[max]->type == AND)
                    {
                        if (Queue->queue[pos]->children[max - 1]->type != IDENTIFIER)
                        {
                            list = makeSearchV(list, searchColumnInd(*Table, Queue->queue[pos]->children[max - 3]->lexeme), atof(Queue->queue[pos]->children[max - 1]->lexeme), Queue->queue[pos]->children[max - 2]->type);
                        }
                        else
                        {
                            list = makeSearchC(list, searchColumnInd(*Table, Queue->queue[pos]->children[max - 3]->lexeme), searchColumnInd(*Table, Queue->queue[pos]->children[max - 1]->lexeme), Queue->queue[pos]->children[max - 2]->type);
                        }
                    }
                    max++;
                }
            }
            pos++;
            if (pos != Queue->queueSize)
            {
                fprintf(stderr, "NEED NOTHING AFTER WHERE\n");
                exit(EXIT_FAILURE);
            }
            if (Queue->queue[0]->type == SELECT && list->size != 0)
            {
                for (int j = 0; j < Columns.size; j++)
                {
                    column *temp = (*Table)->columns[j];
                    for (int i = 0; i < list->size; i++)
                    {
                        printf("%d - value\n", *(int *)temp->Cells[i]->data);
                    }
                }
            }
        }
        else
        {
            fprintf(stderr, "%s - WTF ERROR\n", Queue->queue[pos]->lexeme);
            exit(EXIT_FAILURE);
        }
    }
}

stringInd *makeSearchC(stringInd *list, column *column1, column *column2, tokenType operator)
{
    stringInd *temp = malloc(sizeof(stringInd));

    if (column1->type != column2->type)
    {
        fprintf(stderr, "WRONG TYPES\n");
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
        fprintf(stderr, "WRONG OPERATOR\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

stringInd *makeSearchV(stringInd *list, column *column1, float value, tokenType operator)
{
    stringInd *temp = malloc(sizeof(stringInd));

    // if (column1->type != column2->type)
    // {
    //     fprintf(stderr, "WRONG TYPES");
    //     exit(EXIT_FAILURE);
    // }

    if (operator== EQUAL_TO)
    {
        printf("%f\n", *(float *)column1->Cells[0]->data);

        for (int i = 0; i < column1->size; i++)
        {
            printf("%f - 1v, %f -2v\n", value, *(float *)column1->Cells[i]->data);
            if (*(float *)column1->Cells[i]->data == value)
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
            if (*(float *)column1->Cells[i]->data > value)
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
            if (*(float *)column1->Cells[i]->data < value)
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
        fprintf(stderr, "WRONG OPERATOR\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}