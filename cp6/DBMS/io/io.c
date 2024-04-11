
#include "io.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir("/home/utyfull/Desktop/labs/labs_inf/cp6");
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            int len = strlen(ent->d_name);
            if (len > 4 && strcmp(ent->d_name + len - 4, ".sql") == 0)
            {
                char filePath[1024];
                snprintf(filePath, sizeof(filePath), "%s/%s", "/home/utyfull/Desktop/labs/labs_inf/cp6", ent->d_name);
                FILE *file = fopen(filePath, "r");
                if (file != NULL)
                {
                    table *Table = NULL;
                    // Do something with the opened file, e.g., read content
                    char c = fgetc(file);
                    while (c != EOF)
                    {
                        char *buffer = malloc(sizeof(char) * 1000);
                        int index = 0;
                        while (c != ';' && c != EOF)
                        {
                            buffer[index++] = c;
                            c = fgetc(file);
                        }
                        buffer[index++] = c;
                        buffer[index++] = '\0';
                        // do

                        free(buffer);
                        buffer = NULL;
                        c = fgetc(file);
                    }
                    if (Table != NULL)
                    {
                        writeTableToFile("WTF.db", Table);
                    }
                    fclose(file);
                }
                else
                {
                    fprintf(stderr, "Failed to open file: %s\n", filePath);
                    closedir(dir);
                    exit(EXIT_FAILURE);
                }
            }
        }
        closedir(dir);
    }
    else
    {
        fprintf(stderr, "Failed to open directory");
        return EXIT_FAILURE;
    }
    return 0;
}