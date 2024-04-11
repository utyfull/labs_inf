#ifndef _COLUMN_STRUCT_H_
#define _COLUMN_STRUCT_H_

typedef enum
{
    INTEGER = 0,
    CHAR = 2,
    FLOAT = 1
} type;

typedef struct
{
    type type;
    void *data;
} cell;

typedef struct column
{
    type type;
    char columnName[50];
    cell **Cells;
    int size;
    int id;
} column;

int typeCheck(char *value);
cell *createCell(char *value);
void insertCell(cell *Cell, column *Column);
column *createColumn(char *columnName, int id, type Type);
void freeColumn(column **Column);
void deleteCell(column *Column, int ind);
void printColumn(column *Column);
void freeCell(cell **Cell);

#endif