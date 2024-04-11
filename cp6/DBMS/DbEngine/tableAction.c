
#include "tableStruct.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

table *createTable(char *tableName, int id)
{
    table *newTable = (table *)malloc(sizeof(table));
    newTable->columns = (column **)malloc(sizeof(column *));
    strcpy(newTable->tableName, tableName);
    newTable->size = 0;
    newTable->id = id;
    return newTable;
}

void insertColumn(char *columnName, table **Table, type Type)
{
    (*Table)->columns = (column **)realloc((*Table)->columns, ((*Table)->size + 1) * sizeof(column *));
    column *newColumn = createColumn(columnName, (*Table)->size, Type);
    (*Table)->columns[(*Table)->size] = newColumn;
    (*Table)->size++;
}

void freeTable(table **tbl)
{
    if (tbl == NULL)
    {
        return;
    }

    for (int i = 0; i < (*tbl)->size; i++)
    {
        freeColumn(&(*tbl)->columns[i]);
    }

    free((*tbl)->columns);
    free(*tbl);
}

void deleteColumn(table *Table, int ind)
{
    freeColumn(&Table->columns[ind]);
    for (int i = ind; i < Table->size - 1; i++)
    {
        Table->columns[ind] = Table->columns[ind + 1];
    }
    Table->size--;
}

void insertValue(table **Table, int ind, char *value)
{
    cell *Cell = createCell(value);
    // if ((*Table)->columns[ind] != NULL) freeColumn(&(*Table)->columns[ind]);
    (*Table)->columns[ind] = (column *)realloc((*Table)->columns[ind], sizeof(column) + ((*Table)->columns[ind]->size + 1) * sizeof(cell *));
    insertCell(Cell, (*Table)->columns[ind]);
}

void deleteValue(table *Table, int ind, int cellInd)
{
    deleteCell(Table->columns[ind], cellInd);
}

void printTable(table *Table)
{
    printf("Table Name: %s\n", Table->tableName);
    for (int i = 0; i < Table->size; i++)
    {
        printColumn(Table->columns[i]);
    }
}