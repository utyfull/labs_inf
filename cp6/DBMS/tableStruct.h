#ifndef _TABLE_STRUCT_H_
#define _TABLE_STRUCT_H_

#include "columnStruct.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char tableName;
    column *columns;
    int size;
} table;

table createTable(char *name);

void insertColumn(table *Table, char *name);
void insertIntValue(int value, column *Column, table *Table);
void insertCharValue(char *value, column *Column, table *Table);

column freeColumn(column *Column);
table* freeTable(table *Table);

void deleteIntValue(int value, column *Column, table *Table);
void deleteCharValue(char *value, column *Column, table *Table);
void deleteIndex(int index, table *Table);

void printIntColumn(column *Column);
void printCharColumn(column *Column);

void makeMemory(table *Table, size_t size);

#endif