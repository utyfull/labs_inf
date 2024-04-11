

#include "tableStruct.h"
#include "fileStruct.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkMax(table *Table)
{
    printf("Students with bad math\n");
    for (int i = 0; i < Table->columns[0]->size; i++)
    {
        int flag = 1;
        for (int j = 5; j < Table->size; j++)
        {
            if (*(float *)(Table->columns[j]->Cells[i]->data) <= 4.5)
            {
                flag = 0;
                break;
            }
        }
        if (*(float *)(Table->columns[4]->Cells[i]->data) < 3.5 && flag == 1)
        {
            printf("%s\n", (char *)Table->columns[0]->Cells[i]->data);
        }
    }
    printf("_________________________________________\n");
}
