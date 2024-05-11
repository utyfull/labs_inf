#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Node *createNode(char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *buildTree(char *str, int *index)
{
    if (str[*index] == '\0' || str[*index] == ')')
    {
        return NULL;
    }

    if (isdigit(str[*index]))
    {
        Node *root = createNode(str[*index]);
        (*index)++;
        return root;
    }
    else if (str[*index] == '(')
    {
        // Пропускаем открывающую скобку
        (*index)++;

        Node *root = buildTree(str, index);

        // Следующий символ после рекурсивного вызова должен быть операцией
        root->data = str[*index];
        (*index)++;

        root->left = buildTree(str, index);
        root->right = buildTree(str, index);

        // Следующий символ после правого узла должен быть закрывающей скобкой
        if (str[*index] == ')')
        {
            (*index)++;
        }

        return root;
    }
    else
    {
        // Операция
        Node *root = createNode(str[*index]);
        (*index)++;
        root->left = buildTree(str, index);
        root->right = buildTree(str, index);
        return root;
    }
}

void printTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%c \n", root->data);
    printTree(root->left);
    printTree(root->right);
}

int main()
{
    char str[] = "a + b + c - d";
    int index = 0;
    // Node *root = NULL;

    Node *root = buildTree(str, &index);

    printf("Binary Tree representation of the string: \n");
    printTree(root);

    return 0;
}
