#ifndef _TABLE_STRUCT_H_
#define _TABLE_STRUCT_H_

#include "columnStruct.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char tableName[50];
    column **columns;
    int size;
    int id;
} table;

table* createTable(char* tableName, int id);
void insertColumn(char* columnName, table** Table);
void freeTable(table **tbl);
void deleteColumn(table *Table, int ind);
void insertValue(table **Table, int ind, char* value);
void deleteValue(table *Table, int ind, int cellInd);
void printTable(table *Table);

#endif