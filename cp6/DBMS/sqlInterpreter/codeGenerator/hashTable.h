#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#define TABLE_SIZE 100

typedef struct
{
    char *key;
    int value;
} HashNode;

typedef struct
{
    HashNode *nodes[TABLE_SIZE];
} HashTable;

unsigned int hash(const char *key);
HashTable *create_table();
void insert(HashTable *HTable, const char *key, int value);
int search(HashTable *table, const char *key);
void freeHash(HashTable **HTable);

#endif