

#include "tableStruct.h"
#include "fileStruct.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkMax(table *Table) {
    printf("Students with bad math\n");
    for (int i = 0; i <Table->columns[0]->size; i++) {
        int flag = 1;
        for (int j = 5; j < Table->size; j++) {
            if (*(float*)(Table->columns[j]->Cells[i]->data) <= 4.5) {
                flag = 0;
                break;
            }
        }
        if (*(float*)(Table->columns[4]->Cells[i]->data) < 3.5 && flag == 1) {
            printf("%s\n", (char*)Table->columns[0]->Cells[i]->data);
        }
    }
    printf("_________________________________________\n");
}


int main() {
    char value[50];
    char tableName[50];
    char columnName[50];
    char command[100];
    int ind;

    table *Table = NULL;

    while(1) {
        scanf("%s", command);
        if (strcmp(command, "createTable") == 0) {
            scanf("%s", tableName);
            Table = createTable(tableName, 0);
            continue;
        }
        else if (strcmp(command, "createColumn") == 0) {
            if (Table != NULL) {
            scanf("%s", columnName);
            insertColumn(columnName, &Table);
            } else printf("Create Table!!!!!!!\n");
            continue;
        }
        else if (strcmp(command, "writeData") == 0) {
            writeTableToFile("WTF.db" ,Table);
            continue;
        }
        else if (strcmp(command, "printTask") == 0) {
            checkMax(Table);
            continue;
        }
        else if (strcmp(command, "loadData") == 0) {
            if (Table != NULL) freeTable(&Table);
            readTableFromFile("WTF.db", &Table);
            continue;
        }
        else if (strcmp(command, "printTable") == 0) {
            if (Table != NULL) {
            printTable(Table);
            } else printf("Create TABLEEEEE\n");
            continue;
        }
        else if (strcmp(command, "deleteValue") == 0) {
            scanf("%s", columnName);
            scanf("%d", &ind);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(Table->columns[i]->columnName, columnName) == 0){
                    deleteValue(Table, i, ind);
                }
            }
            continue;
        }
        else if (strcmp(command, "deleteColumn") == 0) {
            scanf("%s", columnName);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(Table->columns[i]->columnName, columnName) == 0){
                    deleteColumn(Table, i);
                }
            }
            continue;
        }
        else if (strcmp(command, "insertValue") == 0) {
            scanf("%s", columnName);
            scanf("%s", value);
            for (int i = 0; i < Table->size; i++) {
                if (strcmp(Table->columns[i]->columnName, columnName) == 0){
                    insertValue(&Table, i, value);
                }
            }
            continue;
        }
        else if (strcmp(command, "exit") == 0) {
            freeTable(&Table);
            break;
        } else {
            printf("Invalid input\n");
            memset(command, 0 , 100);
        }
    }
}

