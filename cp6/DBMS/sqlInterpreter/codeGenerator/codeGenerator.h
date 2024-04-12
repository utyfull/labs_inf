#ifndef _CODE_GENERATOR_H_
#define _CODE_GENERATOR_H_

#include "../semanticAnalizer/semanticAnalizer.h"
#include "../../DbEngine/tableStruct.h"
#include "../../fileManager/fileStruct.h"

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

extern typeRelation types[];

void generate(nodeQueue *Queue, table **TAble);
void queueString(char *String);

#endif