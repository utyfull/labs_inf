
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Binary tree main structure
struct node {
  double item;
  struct node* left;
  struct node* right;
};


// Create a new node
struct node* create(double value) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->item = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}


// Insert value
struct node *insertValue(struct node* root, double value) {
    if (root == NULL) {
        return create(value);
    }

    if (value < root->item) {
        root->left = insertValue(root->left, value);
    } else if (value > root->item) {
        root->right = insertValue(root->right, value);
    }

    return root;
}


// Delete node function
struct node* deleteNode(struct node* root, double value) 
  {
    if (root == NULL) 
    {
      return root;
    }
    
    else
    {
      // node is found and needs to be deleted 
      if(value == root->item) 
      {
        if (root->left == NULL && root->right == NULL) 
        {
          free(root);
          return NULL;
        } 

        else if(root->left == NULL)
        {
          struct node* temp = root->right;
          free(root);
          return temp;
        }

        else if (root->right == NULL) 
        {
          struct node* temp = root->left;
          free(root);
          return temp;
        } 

        else 
        {
          // finding the minimum value in the right subtree
          struct node * min_right_subtree ; 
          struct node * current = root->right;
          while (current->left != NULL) 
          {
            current = current->left;
          }
          min_right_subtree = current;
        
          // switching the values 
          root->item = min_right_subtree->item;

          // Deleting the node with val_to_delete now as a leaf node
          root->right = deleteNode(root->right, min_right_subtree->item);
        }
      }
    
      // keep searching for node
      else
      {
        if (value < root->item) 
        {
          root->left = deleteNode(root->left, value);
        }
        
        else if (value > root->item) 
        {
          root->right = deleteNode(root->right, value);
        }
      }
      
      return root ;
    }
  }

// Print binary tree function
void printTree(struct node *root, int space) { 
    if (root == NULL) { 
        return; 
    } 
 
    space += 5; 
 
    printTree(root->right, space); 
 
    printf("\n"); 
    for (int i = 5; i < space; i++) { 
        printf(" "); 
    } 
 
    printf("%lf\n", root->item); 
 
    printTree(root->left, space); 
} 

// Check leaf level function
int checkUtil(struct node* root, int level, int *leafLevel)
{
    if (root == NULL)  return 1;
 
    if (root->left == NULL && root->right == NULL)
    {
        if (*leafLevel == 0)
        {
            *leafLevel = level;
            return 1;
        }
 
        return (level == *leafLevel);
    }
 
    return checkUtil(root->left, level+1, leafLevel) &&
           checkUtil(root->right, level+1, leafLevel);
}

int check(struct node* root)
{
   int level = 0, leafLevel = 0;
   return checkUtil(root, level, &leafLevel);
}

struct node* freeTree (struct node* root) {
    if (root == NULL) {
      return root;
    }

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}
    


int main() {
    double number;
    char command[100];
    struct node* root = NULL;

  while(1) {
    scanf("%s", command);
    if (strcmp(command, "createTree") == 0) {
      scanf("%lf", &number);
      root = freeTree(root);
      root = create(number);
      continue;
    }
    if (strcmp(command, "insertValue") == 0) {
      scanf("%lf", &number);
      insertValue(root, number);
      continue;
    } 
    if (strcmp(command, "deleteNode") == 0) {
      scanf("%lf", &number);
      root = deleteNode(root, number);
      continue;
    }
    if (strcmp(command, "printTree") == 0) {
      printTree(root, 5);
      continue;
    }
    if (strcmp(command, "checkLL") == 0) {
      printf("Leaves in one level: %d\n", check(root));
      continue;
    }
    if (strcmp(command, "exit") == 0) {
      root = freeTree(root);
      return 0;
    }
    if (strcmp(command, "freeTree") == 0) {
      root = freeTree(root);
      continue;
    }
  }
}



