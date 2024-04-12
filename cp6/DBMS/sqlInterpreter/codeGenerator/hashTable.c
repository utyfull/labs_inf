#include "hashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashTable *create_table()
{
    HashTable *table = malloc(sizeof(HashTable));
    memset(table->nodes, 0, sizeof(table->nodes));
    return table;
}

void insert(HashTable *table, const char *key, int value)
{
    unsigned int index = hash(key);
    HashNode *node = malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    table->nodes[index] = node;
}

int search(HashTable *table, const char *key)
{
    unsigned int index = hash(key);
    if (table->nodes[index] && strcmp(table->nodes[index]->key, key) == 0)
    {
        return table->nodes[index]->value;
    }
    return -1; // Not found
}

void freeHash(HashTable **HTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if ((*HTable)->nodes[i])
        {
            free((*HTable)->nodes[i]->key);
            free((*HTable)->nodes[i]);
        }
    }
    free(*HTable);
}