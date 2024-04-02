

#include "tableStruct.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    char value[50];
    char tableName[50];
    char columnName[50];
    char command[100];

    table *Table = NULL;

    while(1) {
        scanf("%s", command);
        if (strcmp(command, "createTable") == 0) {
            scanf("%s", tableName);
            Table = createTable(tableName, 0);
            continue;
        }
        else if (strcmp(command, "createColumn") == 0) {
            scanf("%s", columnName);
            insertColumn(columnName, &Table);;
            continue;
        }
        else if (strcmp(command, "printTable") == 0) {
            printTable(Table);
            continue;
        }
        else if (strcmp(command, "insertValue") == 0) {
            scanf("%s", columnName);
            scanf("%s", value);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(Table->columns[i]->columnName, columnName) == 0){
                    insertValue(Table, i, value);
                }
            }
            continue;
        }
        else if (strcmp(command, "exit") == 0) {
            if (Table != NULL) {
            freeTable(Table);
            free(Table);
            }
            break;
        } else {
            printf("Invalid input\n");
            memset(command, 0 , 100);
        }
    }
}

