
#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для создания нового узла
Node *createNode(size_t data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в кольцевой список
void append(Node **head, size_t data)
{
    Node *newNode = createNode(data);
    if (!*head)
    {
        *head = newNode;
        newNode->next = *head;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

// Функция для очистки списка
void clearList(Node **head)
{
    if (!*head)
        return;

    Node *current = *head;
    Node *nextNode = NULL;

    while (current->next != *head)
    { // Проходим по всем узлам, кроме последнего, связанного с головой
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(current); // Освобождаем последний узел
    *head = NULL;  // Обнуляем указатель на голову списка
}

// Функция для перестановки первой и второй половины списка
void swapHalves(Node **head)
{
    if (!*head || (*head)->next == *head)
        return; // Если список пуст или содержит один элемент

    Node *slow = *head, *fast = *head, *prev = NULL;
    while (fast->next != *head && fast->next->next != *head)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast->next->next == *head)
    { // Для четного количества элементов
        fast = fast->next;
    }

    Node *mid = slow;
    fast->next = mid->next; // Начало второй половины становится началом списка
    mid->next = *head;      // Конец первой половины указывает на начало списка
    *head = fast->next;     // Обновляем голову списка
}

int listLength(Node *head)
{
    int length = 0;
    Node *current = head;
    if (head == NULL)
        return 0;
    do
    {
        length++;
        current = current->next;
    } while (current != head);
    return length;
}

// Функция для печати списка
void printList(Node *head)
{
    if (head == NULL)
        return;
    Node *temp = head;
    do
    {
        printf("%zu ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

Node *deleteValue(Node *head, size_t value)
{
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL)
    {
        if (current->data == value)
        {
            if (prev == NULL)
            {
                if (current->next != head)
                {
                    head = current->next;
                    Node *temp = current;
                    while (temp->next != head)
                        temp = temp->next;
                    temp->next = head;
                }
                else
                {
                    head = NULL;
                }
                free(current);
                return head;
            }
            prev->next = current->next;
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

int main()
{
    Node *head = NULL;

    char command[100];
    size_t unsignedValue;

    while (1)
    {
        scanf("%s", command);

        if (strcmp(command, "insertValue") == 0)
        {
            scanf("%zu", &unsignedValue);
            append(&head, unsignedValue);
            continue;
        }
        if (strcmp(command, "printList") == 0)
        {
            printList(head);
            continue;
        }
        if (strcmp(command, "listLength") == 0)
        {
            printf("%d  \n", listLength(head));
            continue;
        }
        if (strcmp(command, "swapHalves") == 0)
        {
            swapHalves(&head);
            continue;
        }
        if (strcmp(command, "deleteValue") == 0)
        {
            scanf("%zu", &unsignedValue);
            head = deleteValue(head, unsignedValue);
            continue;
        }
        if (strcmp(command, "exit") == 0)
        {
            clearList(&head);
            return 0;
        }
    }
}