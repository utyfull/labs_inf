
#include "header.h"

#include <stdio.h>
#include <stdlib.h>



// Функция для создания нового узла
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в кольцевой список
void append(Node** head, int data) {
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

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    append(&head, 6);


    while (1) {
        
        scanf("%s", command);

        if ()
    }

    printf("Исходный список:\n");
    printList(head);

    swapHalves(&head);

    printf("Список после перестановки половин:\n");
    printList(head);

    return 0;
}