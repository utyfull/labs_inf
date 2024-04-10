
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
                // Do something with the opened file, e.g., read content
                printf("Opened file: %s\n", filePath);
                fclose(file);
            }
            else
            {
                fprintf(stderr, "Failed to open file: %s\n", filePath);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            fprintf(stderr, "Failed to find file with suffix .sql");
            exit(EXIT_FAILURE);
        }
    }
    closedir(dir);
}