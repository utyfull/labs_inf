
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
        newCell->data = (void*)malloc(strlen(value) + 1);  // Выделяем достаточно места для хранения всей строки, включая завершающий нулевой символ
        strcpy((char*)(newCell->data), value);
    }
    
    return newCell;
}
    

int typeCheck(char *value) {
    int iter = 0;
    int flag = 0;
    while (value[iter]) {
        if (isalpha(value[iter])) {
            flag = 2;
        } else if (value[iter] == '.' && flag != 2) {
            flag = 1;
        }
        iter++;
    }
    return flag;
}


void insertCell(cell *Cell, column *Column) {
    //if (Column->Cells != NULL) free(Column->Cells);
    Column->Cells = (cell**)realloc(Column->Cells, (Column->size + 1) * sizeof(cell*));
    Column->Cells[Column->size] = Cell;
    Column->size++;
}

column* createColumn(char* columnName, int id) {
    column* newColumn = (column*)malloc(sizeof(column));
    newColumn->Cells = (void*)malloc(sizeof(cell));
    strcpy(newColumn->columnName, columnName);
    newColumn->id = id;
    newColumn->size = 0;
    return newColumn;
}



void freeColumn(column **Column) {
    if (*Column == NULL) {
        return;
    }

    for (int i = 0; i < (*Column)->size; i++) {
        free((*Column)->Cells[i]->data);
        free((*Column)->Cells[i]);
    }

    free((*Column)->Cells);
    free((*Column)->columnName);
}

void freeCell(cell **Cell) {
    free((*Cell)->data);
    free(*Cell);
}

void deleteCell(column* Column, int ind) {
    if (Column->Cells[ind] != NULL) {
        freeCell(&Column->Cells[ind]);
        Column->Cells[ind] = NULL;
    }
    for (int i = ind; i < Column->size - 1; i++) {
        Column->Cells[i] = Column->Cells[i + 1];
    }
    Column->size--;
}


void printColumn(column* Column) {
    printf("Column Name: %s\n", Column->columnName);
    for (int i = 0; i < Column->size; i++) {
        // Print column data
        if (Column->Cells[i]->type == 0) printf("%d", *(int*)Column->Cells[i]->data); 
        if (Column->Cells[i]->type == 1) printf("%f", *(float*)Column->Cells[i]->data);  
        if (Column->Cells[i]->type == 2) printf("%s", (char*)Column->Cells[i]->data);
        
        // Determine if a space or new line should be printed
        if (i != Column->size - 1) { 
            printf(" ");
        } else {  // Print new line if it's the last data item
            printf("\n");
        }
    }
}