
#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void insertAtIndex(Node **head, Node *value, int index)
{
    Node *temp = *head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    value->next = temp->next;
    temp->next = value;
}

// Функция для перестановки первой и второй половины списка
void swapHalves(Node **head)
{
    int midIndex = floor(listLength(*head) / 2);
    if (listLength(*head) % 2 == 0)
    {
        for (int i = 0; i < midIndex; i++)
        {
            *head = (*head)->next;
        }
    }
    else
    {
        Node *temp = *head;
        Node *loh;
        for (int i = 0; i < midIndex; i++)
        {
            temp = temp->next;
            if (i == midIndex - 1)
            {
                loh = deleteValue(head, temp->data);
            }
        }
        swapHalves(head);
        insertAtIndex(head, loh, midIndex);
    }
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

Node *deleteValue(Node **head, size_t value)
{
    Node *save = NULL;
    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL)
    {
        if (current->data == value)
        {

            save = (Node *)malloc(sizeof(Node));
            save->data = current->data;
            save->next = NULL;

            if (current == *head)
            {

                if (current->next != *head)
                {
                    Node *last = current;
                    while (last->next != *head)
                        last = last->next;
                    *head = current->next;
                    last->next = *head;
                }
                else
                {
                    *head = NULL;
                }

                if (current->next == current) // If there is only one node in the list
                    *head = NULL;
            }
            else
            {

                prev->next = current->next;
            }

            if (current == *head)
                *head = current->next;

            Node *toFree = current;
            current = current->next;
            free(toFree);
            break;
        }
        else
        {
            prev = current;
            current = current->next;
            if (current == *head)
                break;
        }
    }
    return save;
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
            Node *bespolezn;
            scanf("%zu", &unsignedValue);
            bespolezn = deleteValue(&head, unsignedValue);
            free(bespolezn);
            continue;
        }
        if (strcmp(command, "exit") == 0)
        {
            clearList(&head);
            return 0;
        }
    }
}