#ifndef _CP9_H_
#define _CP9_H_

typedef struct
{
    char key[12][16];
    char content[12][255];
    int countK;
    int countC;
} table;

void sortTable(table **Table);
void insertData(table **Table);
void binarySearch(table *Table, char *key);
void printTable(table *Table);

#endif