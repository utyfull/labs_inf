#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
Node* insertEnd(Node* head, int data) {
    Node* newNode = createNode(data);

    if (head == NULL) {
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

void bubbleHelp(Node **ptr, int *temp, int *swapped) {
    if ((*ptr)->data > (*ptr)->next->data) {
            *temp = (*ptr)->data;
            (*ptr)->data = (*ptr)->next->data;
            (*ptr)->next->data = *temp;
            *swapped = 1;
        }
}


// Bubble sort function for linked list
void bubbleSort(Node* head) {
    int swapped, temp = 0;
    Node* ptr;
    Node* lptr = NULL;

    if (head == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != lptr) {
            bubbleHelp(&ptr, &temp, &swapped);
        ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}

void deleteNode(Node** head_ref, int position) {
    if (*head_ref == NULL) {
        return;
    }

    Node* temp = *head_ref;

    // Если удаляемый элемент - первый
    if (position == 0) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // Найти предыдущий узел i-го узла
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // Если i больше длины списка, не делаем ничего
    if (temp == NULL || temp->next == NULL) {
        return;
    }

    // Удаление узла, соединение предыдущего узла с последующим
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

void replaceNodeAtIndex(Node* head, int index, int new_data) {
    Node* current = head;
    int i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Индекс превышает длину списка\n");
        return;
    }

    current->data = new_data;
}

void insertAfterIndex(Node** head_ref, int index, int new_data) {
    if (*head_ref == NULL) {
        printf("Список пуст\n");
        return;
    }

    Node* current = *head_ref;
    int i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Индекс превышает длину списка\n");
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    new_node->data = new_data;
    new_node->next = current->next;
    current->next = new_node;
}

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free memory allocated for the linked list
void freeList(Node* head) {
    Node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    char command[100];
    int pos;
    int value;

    while (1) {
        scanf("%s", command);

        if (strcmp(command, "insertEnd") == 0) {
            scanf("%d", &value);
            head = insertEnd(head, value);
            continue;
        }
        if (strcmp(command, "bubbleSort") == 0) {
            bubbleSort(head);
            continue;
        }
        if (strcmp(command, "printList") == 0) {
            printList(head);
            continue;
        }
        if (strcmp(command, "replaceValue") == 0) {
            scanf("%d", &pos);
            scanf("%d", &value);
            replaceNodeAtIndex(head, pos, value);
            continue;
        }
        if (strcmp(command, "insertAfter") == 0) {
            scanf("%d", &pos);
            scanf("%d", &value);
            insertAfterIndex(&head, pos, value);
            continue;
        }
        if (strcmp(command, "deleteValue") == 0) {
            scanf("%d", &pos);
            deleteNode(&head, pos);
            continue;
        }
        if (strcmp(command, "exit") == 0) {
            freeList(head);
            return 0;
        }

    }
}