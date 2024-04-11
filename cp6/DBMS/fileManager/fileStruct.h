
#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include "../DbEngine/tableStruct.h"

void writeTableToFile(const char *filename, table *t);
void readTableFromFile(const char *filename, table **t);

#endif
