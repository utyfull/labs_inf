
#include "tableStruct.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    int value;
    char charValue[100];
    char tableName[100];
    char columnName[100];
    char columnNameList[100][10];
    char command[100];
    int columnNameInd = 0;

    table *Table = NULL;
    Table = malloc(sizeof(table));

    while(1) {
        scanf("%s", command);
        if (strcmp(command, "createTable") == 0) {
            scanf("%s", tableName);
            *Table = createTable(tableName);
            continue;
        }
        if (strcmp(command, "createColumn") == 0) {
            scanf("%s", columnName);
            strcpy(columnNameList[columnNameInd], columnName);
            insertColumn(Table, columnNameList[columnNameInd]);
            columnNameInd++;
            for (int i = 0; i < 3; i++) {
            //printf("%s - column name, %d - id\n", Table->columns[i].columnName, Table->columns[i].id);
            }
            continue;
        } 
        if (strcmp(command, "insertCharValue") == 0) {
            scanf("%s", columnName);
            scanf("%s", charValue);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(&Table->columns[i].columnName, columnName) == 0) {
                    insertCharValue(charValue, &Table->columns[i], Table);
                }
            }
            printf("%s - value\n", Table->columns[0].data[Table->columns->size - 1].Citem);
            printf("%d - size\n", Table->columns[0].size);
            continue;
        }
        if (strcmp(command, "insertIntValue") == 0) {
            scanf("%s", columnName);
            scanf("%d", &value);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(&Table->columns[i].columnName, columnName) == 0) {
                    insertIntValue(value, &Table->columns[i], Table);
                }
            }
            //printf("%d - value\n", Table->columns[0].data[0].Iitem);
            continue;
        }
        if (strcmp(command, "printCharColumn") == 0) {
            scanf("%s", columnName);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(&Table->columns[i].columnName, columnName) == 0) {
                    printCharColumn(&Table->columns[i]);
                }
            }
            continue;
        }
        if (strcmp(command, "printIntColumn") == 0) {
            scanf("%s", columnName);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(&Table->columns[i].columnName, columnName) == 0) {
                    printIntColumn(&Table->columns[i]);
                }
            }
            continue;
        }
        if (strcmp(command, "deleteCharValue") == 0) {
            scanf("%s", columnName);
            scanf("%s", charValue);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(&Table->columns[i].columnName, columnName) == 0) {
                    deleteCharValue(charValue, &Table->columns[i], Table);
                }
            }
            continue;
        }

        if (strcmp(command, "deleteIntValue") == 0) {
            scanf("%s", columnName);
            scanf("%d", &value);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(&Table->columns[i].columnName, columnName) == 0) {
                    deleteIntValue(value, &Table->columns[i], Table);
                }
            }
            continue;
        }

        if (strcmp(command, "deleteTable") == 0) {
            Table = freeTable(Table);
            continue;
        }
        if (strcmp(command, "exit") == 0) {
            freeTable(Table);
            break;
        }
        if (strcmp(command, EOF) == 0) {
            freeTable(Table);
            break;
        }
    }
}

