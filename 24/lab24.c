#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

Node *createNode(char *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int toSqrt(int num)
{
    double squareRoot = sqrt((double)num);
    if ((int)squareRoot == squareRoot)
    {
        return (int)squareRoot;
    }
    else
    {
        fprintf(stderr, "Cant extract square!\n");
        exit(EXIT_FAILURE);
    }
}

void makeSumSquare(Node *root)
{
    checkOperators(root);
    int a = toSqrt(atoi(root->left->data));
    int b = toSqrt(atoi(root->right->right->data));
    int twOab = (int)(atoi(root->right->left->data) / 2);

    if (a * b == twOab)
    {
        printf("(%d + %d)^2\n", a, b);
    }
    else
    {
        fprintf(stderr, "Can't create square!\n");
        exit(EXIT_FAILURE);
    }
}

void checkOperators(Node *root)
{
    if (strcmp(root->data, "+") != 0 || strcmp(root->right->data, "+") != 0)
    {
        fprintf(stderr, "Wrong operator while creating sum square!\n");
        exit(EXIT_FAILURE);
    }
}

Node *buildTree(char *str, char *sep)
{
    if (str == NULL || *str == ')')
    {
        return NULL;
    }

    if (1)
    {
        Node *root = NULL;
        char temp[100];
        strcpy(temp, str);
        if (strcmp(temp, "-") == 0 || strcmp(temp, "+") == 0)
        {
            fprintf(stderr, "Wrong operator position!\n");
            exit(EXIT_FAILURE);
        }
        str = strtok(NULL, sep);

        if (str != NULL)
        {
            root = createNode(str);
            root->left = createNode(temp);
            str = strtok(NULL, sep);
            root->right = buildTree(str, sep);
        }
        else
        {
            root = createNode(temp);
        }
        return root;
    }
}

void printTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%s \n", root->data);
    printTree(root->left);
    printTree(root->right);
}

void freeRoot(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    freeRoot(root->left);
    freeRoot(root->right);
    free(root->data);
}

int main()
{

    // char str[] = "4 + 8 + 4";
    char str[100];
    scanf("%99[^\n]", str);

    if (strcmp(str, "") == 0)
    {
        fprintf(stderr, "Need five arguments, 0 given!\n");
        exit(EXIT_FAILURE);
    }
    char *str_copy = strdup(str);
    char *newstr = strtok(str_copy, " ");

    Node *root = buildTree(newstr, " ");

    printf("Binary Tree representation of the string: \n");
    printTree(root);

    makeSumSquare(root);

    free(str_copy);
    freeRoot(root);

    return 0;
}
