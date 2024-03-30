#include "tableStruct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void makeMemory(table *Table, size_t size) {
    table *memTable = (table *)realloc(Table, sizeof(table) + size + sizeof(column) * (Table->size + 1));
    if (memTable == NULL) {
        printf("TABLE MEMORY ERROR!!!\n");
    } else {
        Table = memTable;
    }

    column *memColumn = (column *)malloc(sizeof(column) * (Table->size + 1) + size);
    if (memColumn == NULL) {
        printf("COLUMN MEMORY ERROR!!!\n");
    } else {

        Table->columns = memColumn;
    }
}

table createTable(char *name) {
    table *newTable = (table *)malloc(sizeof(table));
    strcpy(&newTable->tableName, name);
    newTable->columns = NULL; // Initialize to NULL
    newTable->size = 0;
    return *newTable;
}

table* freeTable(table *Table) {
    for (int i = 0; i < Table->size; i++) {
        freeColumn(&Table->columns[i]);
    }
    Table->size = 0;
    free(Table);
    return Table;
}

void insertColumn(table *Table, char *name) {
    size_t size = sizeof(column) + strlen(name) + 1;
    makeMemory(Table, size);
    Table->columns[Table->size] = *createColumn(name);
    Table->columns[Table->size].id = Table->size;
    Table->size += 1;
}

void insertIntValue(int value, column *Column, table *Table) {
    size_t newSize = (Column->size + 1) * sizeof(int);
    Column->data = realloc(Column->data, sizeof(Column->data) * (Column->size + 1) + newSize);
    Column->data[Column->size].Iitem = value;
    Column->size += 1;
}

void insertCharValue(char *value, column *Column, table *Table) {
    size_t newSize = (Column->size + 1) * sizeof(char[100]);
    Column->data = realloc(Column->data, sizeof(Column->data) * (Column->size + 1) + newSize);
    strcpy(Column->data[Column->size].Citem, value);
    Column->size += 1;
}

void deleteColumn(table *Table, int columnIndex) {
    freeColumn(&Table->columns[columnIndex]);
    for (int i = columnIndex; i < Table->size - 1; i++) {
        Table->columns[i] = Table->columns[i + 1];
    }
    Table->size -= 1;
}

void deleteIntValue(int value, column *Column, table *Table) {
    int index = -1;
    for (int i = 0; i < Column->size; i++) {
        if (Column->data[i].Iitem == value) {
            index = i;
            break;
        }
    }
    if(index != -1){
        for (int i = index; i < Column->size - 1; i++) {
            Column->data[i] = Column->data[i + 1];
        }
        Column->size -= 1;
        Column->data = realloc(Column->data, Column->size * sizeof(int));
    }
}

void deleteCharValue(char *value, column *Column, table *Table) {
    int index = -1;
    for (int i = 0; i < Column->size; i++) {
        if (strcmp(Column->data[i].Citem, value) == 0) {
            index = i;
            break;
        }
    }
    if(index != -1){
        for (int i = index; i < Column->size - 1; i++) {
            Column->data[i] = Column->data[i + 1];
        }
        Column->size -= 1;
        Column->data = realloc(Column->data, Column->size * sizeof(char*));
    }
}

column freeColumn(column *Column) {
    if(Column->data != NULL){
        free(Column->data);
    }
    Column->size = 0;
    return *Column;
}

void printCharColumn(column *Column) {
    for (int i = 0; i < Column->size; i++) {
        printf("%s\n", Column->data[i].Citem);
    }
}

void printIntColumn(column *Column) {
    for (int i = 0; i < Column->size; i++) {
        printf("%d\n", Column->data[i].Iitem);
    }
}