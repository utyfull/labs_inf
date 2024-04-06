
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_LENGTH 20
#define MAX_GROUP_NUMBER 100

// Функция для генерации случайного имени
char* randomName() {
    static const char* names[] = {"Ivan", "Alex", "Maria", "Olga", "John", "Alice", "Peter", "Anna"};
    static const char* surnames[] = {"Smith", "Johnson", "Brown", "Taylor", "Wilson", "Davis", "Miller"};
    char* name = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
    sprintf(name, "%s", surnames[rand() % (sizeof(surnames) / sizeof(surnames[0]))]);
    return name;
}

// Функция для генерации случайного номера группы
int randomGroupNumber() {
    return rand() % MAX_GROUP_NUMBER + 1;
}

// Функция для генерации случайной оценки
float randomGrade() {
    return (rand() % 5) + (float)(rand() % 10) / 10.0 + 1.0;
}

// Функция для создания таблицы
void createTable(FILE* file, const char* tableName) {
    fprintf(file, "createTable %s\n", tableName);
}

// Функция для создания колонки
void createColumn(FILE* file, const char* columnName) {
    fprintf(file, "createColumn %s\n", columnName);
}

// Функция для вставки значения
void insertValue(FILE* file, const char* columnName, float value) {
    fprintf(file, "insertValue %s %.1f\n", columnName, value);
}

int main() {
    srand(time(NULL));
    
    FILE* file = fopen("./DBMS/data.txt", "w"); // Открытие файла для записи
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    
    createTable(file, "Study"); // Создание таблицы
    
    createColumn(file, "Name");
    createColumn(file, "Initials");
    createColumn(file, "Gender");
    createColumn(file, "Group");
    createColumn(file, "Math");
    createColumn(file, "Physics");
    createColumn(file, "Chemistry");
    createColumn(file, "History");
    createColumn(file, "Literature");

    // Генерация данных
    for (int i = 0; i < 5; i++) {
        fprintf(file, "insertValue Name %s\n", randomName());
        fprintf(file, "insertValue Initials %c.%c.\n", 'A' + rand() % 26, 'A' + rand() % 26);
        fprintf(file, "insertValue Gender %s\n", (rand() % 2 == 0 ? "Male" : "Female"));
        fprintf(file, "insertValue Group %d\n", randomGroupNumber());
        fprintf(file, "insertValue Math %.1f\n", randomGrade());
        fprintf(file, "insertValue Physics %.1f\n", randomGrade());
        fprintf(file, "insertValue Chemistry %.1f\n", randomGrade());
        fprintf(file, "insertValue History %.1f\n", randomGrade());
        fprintf(file, "insertValue Literature %.1f\n", randomGrade());
    }

    fprintf(file, "printTable\n");
    fprintf(file, "writeData\n");
    fprintf(file, "printTask\n");
    fprintf(file, "exit\n");

    fclose(file); // Закрытие файла
    
    return 0;
}