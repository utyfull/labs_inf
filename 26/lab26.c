#include "header.h"

#include <stdio.h>
#include <stdlib.h>



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

    // Insert nodes into the linked list
    head = insertEnd(head, 5);
    head = insertEnd(head, 2);
    head = insertEnd(head, 8);
    head = insertEnd(head, 1);

    // Bubble sort the linked list
    bubbleSort(head);

    // Print the sorted linked list
    printList(head);

    // Free memory allocated for the linked list
    freeList(head);

    return 0;
}