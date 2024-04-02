
#include "tableStruct.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


table* createTable(char* tableName, int id) {
    table* newTable = (table*)malloc(sizeof(table));
    strcpy(newTable->tableName, tableName);
    newTable->size = 0;
    newTable->id = id;
    return newTable;
}

void insertColumn(char* columnName, table **Table) {
    column* newColumn = createColumn(columnName, (*Table)->size);
    *Table = (table*)realloc(*Table, sizeof(*(*Table)) + sizeof(*newColumn));
    (*Table)->columns = (column**)realloc((*Table)->columns, sizeof(*((*Table)->columns)) + sizeof(*newColumn));
    (*Table)->columns[(*Table)->size - 1] = newColumn;
}

void freeTable(table *Table) {
    for (int i = 0; i < Table->size; i++) {
        freeColumn(Table->columns[i]);
    }
    free(Table->columns);
}

void deleteColumn(table *Table, int ind) {
    size_t size = sizeof(*Table->columns[ind]);
    freeColumn(Table->columns[ind]);
    for (int i = ind; i < Table->size - 1; i++) {
        Table->columns[ind] = Table->columns[ind + 1];
    }
    Table->size--;
    Table->columns = (column**)realloc(Table->columns, sizeof(*Table->columns) - size);
    Table = (table*)realloc(Table, sizeof(*Table) - size);
}

void insertValue(table *Table, int ind, char* value) {
    cell* Cell = createCell(value);
    Table = (table*)realloc(Table, sizeof(*Table) + sizeof(*Cell));
    insertCell(Cell, Table->columns[ind]);
}

void deleteValue(table *Table, int ind, int cellInd) {
    size_t size = sizeof(*Table->columns[ind]->Cells[cellInd]);
    deleteCell(Table->columns[ind], cellInd);
    Table = (table*)realloc(Table, sizeof(*Table) - size);
}

void printTable(table *Table) {
    printf("________---------_______%s_________-------_______\n", Table->tableName);
    for (int i = 0; i < Table->size; i++) {
        printColumn(Table->columns[i]);
    }
}