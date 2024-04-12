#ifndef _CODE_GENERATOR_H_
#define _CODE_GENERATOR_H_

#include "../semanticAnalizer/semanticAnalizer.h"
#include "../../DbEngine/tableStruct.h"
#include "../../fileManager/fileStruct.h"
#include "hashTable.h"

#define NUM_TYPES 2

typedef struct
{
    tokenType token;
    type type;
} typeRelation;

typedef struct
{
    int id[20];
    int size;
} columnList;

typedef struct
{
    int ind[100];
    int size;
} stringInd;

extern typeRelation types[];

void generate(nodeQueue *Queue, table **TAble);
void queueString(char *String);
stringInd *makeSearchC(stringInd *list, column *column1, column *column2, tokenType operator);
stringInd *makeSearchV(stringInd *list, column *column1, void *value, tokenType operator);

#endif