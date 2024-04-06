
#include "header.h"

#include <stdio.h>
#include <stdlib.h>



// Функция для создания нового узла
Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    strcpy(newNode->data, data);
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в кольцевой список
void append(Node** head, char* data) {
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        newNode->next = *head;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

// Функция для очистки списка
void clearList(Node** head) {
    if (!*head) return;

    Node* current = *head;
    Node* nextNode = NULL;

    while (current->next != *head) { // Проходим по всем узлам, кроме последнего, связанного с головой
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(current); // Освобождаем последний узел
    *head = NULL; // Обнуляем указатель на голову списка
}

// Функция для перестановки первой и второй половины списка
void swapHalves(Node** head) {
    if (!*head || (*head)->next == *head) return; // Если список пуст или содержит один элемент

    Node *slow = *head, *fast = *head, *prev = NULL;
    while (fast->next != *head && fast->next->next != *head) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast->next->next == *head) { // Для четного количества элементов
        fast = fast->next;
    }

    Node* mid = slow;
    fast->next = mid->next; // Начало второй половины становится началом списка
    mid->next = *head; // Конец первой половины указывает на начало списка
    *head = fast->next; // Обновляем голову списка
}

int listLength(Node* head) {
    int length = 0;
    Node* current = head;
    if (head == NULL) return 0;
    do {
        length++;
        current = current->next;
    } while (current != head);
    return length;
}

// Функция для печати списка
void printList(Node* head) {
    if (!head) return;
    Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    Node* head = NULL;

    char command[100];
    unsigned char* value;

    while (1) {
        scanf("%s", command);

        if (strcmp(command, "insertValue") == 0) {
            scanf("%s", value);
            append(&head, value);
            continue;
        }
        if (strcmp(command, "printList") == 0) {
            printList(head);
            continue;
        }
        if (strcmp(command, "deleteValue") == 0) {
            continue;
        }
        if (strcmp(command, "exit") == 0) {
            clearList(&head);
            return 0;
        }

    }
}