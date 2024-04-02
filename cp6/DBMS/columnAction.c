
#include "columnStruct.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


cell* createCell(char *value) {
    cell* newCell = (cell*)malloc(sizeof(cell));
    newCell->type = typeCheck(value);
    if (newCell->type == 0) {
        newCell->data = (void*)malloc(sizeof(int));
        *(int*)(newCell->data) = atoi(value);
    } else if (newCell->type == 1) {
        newCell->data = (void*)malloc(sizeof(float));
        *(float*)(newCell->data) = atof(value);
    } else {
        *(char*)(newCell->data) = *value;
    }
    return newCell;
}


int typeCheck(char *value) {
    int iter = 0;
    int flag = 0;
    while (value[iter]) {
        if (value[iter] == '.') {
            flag = 1;
        } else if (isalpha(value[iter])) {
            flag = 2;
        }
        iter++;
    }
    return flag;
}

void freeCell(cell *Cell) {
    free(Cell->data);
    free(Cell);
}

void insertCell(cell *Cell, column *Column) {
    Column = (column*)realloc(Column, sizeof(*Column) + sizeof(*Cell));
    Column->Cells = (cell**)realloc(Column->Cells, sizeof(*Column->Cells) + sizeof(*Cell));
    Column->Cells[Column->size] = Cell;
    Column->size++;
}

column* createColumn(char* columnName, int id) {
    column* newColumn = (column*)malloc(sizeof(column));
    strcpy(newColumn->columnName, columnName);
    newColumn->id = id;
    newColumn->size = 0;
    return newColumn;
}

void freeColumn(column *Column) {
    for (int i = 0; i < Column->size; i++) {
        freeCell(Column->Cells[i]);
    }
    free(Column->Cells);
}

void deleteCell(column* Column, int ind) {
    size_t size = sizeof(*Column->Cells[ind]);
    freeCell(Column->Cells[ind]);
    for (int i = ind; i < Column->size - 1; i++) {
        Column->Cells[i] = Column->Cells[i + 1];
    }
    Column->size--;
    Column->Cells = (cell**)realloc(Column->Cells, sizeof(*Column->Cells) - size);
    Column = (column*)realloc(Column, sizeof(*Column) - size);
}

char* getCharData(cell *Cell) {
    return (char*)(Cell->data);
}

void printColumn(column* Column) {
    printf("%s  -  ", Column->columnName);
    for (int i = 0; i < Column->size; i++) {
        if (i != Column->size) {
            printf("%s  ", getCharData(Column->Cells[i]));
        } else {
            printf("%s \n", getCharData(Column->Cells[i]));
        }
    }
}