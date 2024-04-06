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

// Bubble sort function for linked list
void bubbleSort(Node* head) {
    int swapped, temp;
    Node* ptr;
    Node* lptr = NULL;

    if (head == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != lptr) {
            if (ptr->data > ptr->next->data) {
                temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
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
        if (strcmp(command, "exit") == 0) {
            freeList(head);
            return 0;
        }

    }
}