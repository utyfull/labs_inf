
#include "columnStruct.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

column* createColumn(char *name) {
    column* newColumn = (column*)malloc(sizeof(column)); // Allocate memory for the column
    strcpy(&newColumn->columnName, name);
    newColumn->data = malloc(sizeof(newColumn->data)); // Initialize data
    newColumn->size = 0; // Initialize size to 0
    newColumn->id = 0;
    return newColumn;
}
