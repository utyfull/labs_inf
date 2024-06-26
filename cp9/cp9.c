#include "cp9.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortTable(table **Table)
{
    int i, j;
    char temp[255];

    for (i = 0; i < (*Table)->countK - 1; i++)
    {
        for (j = 0; j < (*Table)->countK - i - 1; j++)
        {
            if (strcmp((*Table)->key[j], (*Table)->key[j + 1]) > 0)
            {
                strcpy(temp, (*Table)->key[j]);
                strcpy((*Table)->key[j], (*Table)->key[j + 1]);
                strcpy((*Table)->key[j + 1], temp);

                strcpy(temp, (*Table)->content[j]);
                strcpy((*Table)->content[j], (*Table)->content[j + 1]);
                strcpy((*Table)->content[j + 1], temp);
            }
        }
    }
}

void insertData(table **Table)
{
    (*Table) = (table *)malloc(sizeof(table));
    (*Table)->countK = 0;
    FILE *file = fopen("keys3.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char key[16];

    while (fgets(key, sizeof(key), file) != NULL)
    {
        for (int i = 0; i < 16; i++)
        {
            if (key[i] == '\n')
            {
                key[i] = '\0';
            }
        }
        strcpy((*Table)->key[(*Table)->countK++], key);
    }

    fclose(file);
    (*Table)->countC = 0;
    FILE *file2 = fopen("content3.txt", "r");
    if (file2 == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char content[255];

    while (fgets(content, sizeof(content), file2) != NULL)
    {
        strcpy((*Table)->content[(*Table)->countC++], content);
    }

    fclose(file2);
}

void binarySearch(table *Table, char *key)
{
    int low = 0;
    int high = Table->countK - 1;
    int mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (strcmp(Table->key[mid], key) == 0)
        {
            printf("Key: %s, Value: %s\n", Table->key[mid], Table->content[mid]);
            return;
        }
        else if (strcmp(Table->key[mid], key) < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    printf("Key not found\n");
}

void printTable(table *Table)
{
    if (Table == NULL)
    {
        fprintf(stderr, "Tak delat ne nado, proveryalshik\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < Table->countK; i++)
    {
        printf("Key: %s\nValue: %s\n", Table->key[i], Table->content[i]);
    }
}

int main()
{
    table *Table = NULL;

    char command[100];
    char key[16];

    while (1)
    {
        scanf("%s", command);

        if (strcmp(command, "insertData") == 0)
        {
            insertData(&Table);
            continue;
        }
        if (strcmp(command, "sortTable") == 0)
        {
            printTable(Table);
            sortTable(&Table);
            printf("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
            printTable(Table);
            continue;
        }
        if (strcmp(command, "binarySearch") == 0)
        {
            scanf("%s", key);
            binarySearch(Table, key);
            continue;
        }
        if (strcmp(command, "printTable") == 0)
        {
            printTable(Table);
            continue;
        }
        if (strcmp(command, "exit") == 0)
        {
            free(Table);
            return 0;
        }
    }
}