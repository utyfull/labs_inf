
#include "fileStruct.h"

#include <stdio.h>
#include <string.h>

void writeTableToFile(const char *filename, table *t)
{
    FILE *file = fopen("/home/utyfull/Desktop/labs/labs_inf/cp6/WTF.db", "wb");
    if (file == NULL)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fwrite(t, sizeof(table), 1, file); // Записываем структуру table в файл

    for (int i = 0; i < t->size; i++)
    {
        fwrite(t->columns[i], sizeof(column), 1, file); // Записываем структуру column в файл

        for (int j = 0; j < t->columns[i]->size; j++)
        {
            cell *currentCell = t->columns[i]->Cells[j];
            fwrite(currentCell, sizeof(cell), 1, file); // Записываем структуру cell в файл

            // Записываем данные в ячейке в зависимости от типа
            if (currentCell->type == INTEGER)
            {
                fwrite(currentCell->data, sizeof(int), 1, file);
            }
            else if (currentCell->type == FLOAT)
            {
                fwrite(currentCell->data, sizeof(float), 1, file);
            }
            else if (currentCell->type == CHAR)
            {
                int len = strlen(currentCell->data);                // Получаем длину строки
                fwrite(&len, sizeof(int), 1, file);                 // Записываем длину строки
                fwrite(currentCell->data, sizeof(char), len, file); // Записываем строку
            }
        }
    }
    fclose(file);
}

void readTableFromFile(const char *filename, table **t)
{
    FILE *file = fopen("/home/utyfull/Desktop/labs/labs_inf/cp6/WTF.db", "rb");
    if (file == NULL)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    *t = (table *)malloc(sizeof(table));
    fread(*t, sizeof(table), 1, file); // Читаем структуру table из файла
    (*t)->columns = malloc(sizeof(column));

    for (int i = 0; i < (*t)->size; i++)
    {
        (*t)->columns[i] = (column *)malloc(sizeof(column));
        fread((*t)->columns[i], sizeof(column), 1, file); // Читаем структуру column из файла
        (*t)->columns[i]->Cells = malloc(sizeof(cell) * 10);
        for (int j = 0; j < (*t)->columns[i]->size; j++)
        {
            (*t)->columns[i]->Cells[j] = malloc(sizeof(cell));
            fread((*t)->columns[i]->Cells[j], sizeof(cell), 1, file); // Читаем структуру cell из файла

            // Читаем данные в ячейке в зависимости от типа
            if ((*t)->columns[i]->Cells[j]->type == INTEGER)
            {
                (*t)->columns[i]->Cells[j]->data = malloc(sizeof(int));
                fread((*t)->columns[i]->Cells[j]->data, sizeof(int), 1, file);
            }
            else if ((*t)->columns[i]->Cells[j]->type == FLOAT)
            {
                (*t)->columns[i]->Cells[j]->data = malloc(sizeof(float));
                fread((*t)->columns[i]->Cells[j]->data, sizeof(float), 1, file);
            }
            else if ((*t)->columns[i]->Cells[j]->type == CHAR)
            {
                int len;
                fread(&len, sizeof(int), 1, file);                                           // Читаем длину строки
                (*t)->columns[i]->Cells[j]->data = (char *)malloc((len + 1) * sizeof(char)); // Выделяем память под строку
                fread((*t)->columns[i]->Cells[j]->data, sizeof(char), len, file);            // Читаем строку
                // currentCell->data[len] = '\0'; // Устанавливаем завершающий нуль
            }
        }
    }
    fclose(file);
}
