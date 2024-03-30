#ifndef _COLUMN_STRUCT_H_
#define _COLUMN_STRUCT_H_


typedef struct column{
    char columnName[100];
    union {
    int Iitem;
    char Citem[100];
    } *data;
    int size;
    int id;
} column;

column* createColumn(char *name);


#endif