/* COP 3502C Final Term Assignment 2
This program is written by: Anthony Galbo */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct treeNode
{
    char word[SIZE];
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

FILE *openFile, *outFile;
treeNode *node;

treeNode *createNode(char *word);
void searchFunction(char word[], treeNode **root, treeNode **location);
void searchWord(char word[]);
void insertFunction(char word[]);
void insertWord(char word[]);
void isLeaf(treeNode *root, treeNode *location);
void oneEmpty(treeNode *root, treeNode *location);
void noneEmpty(treeNode *root, treeNode *location);
void deleteWord(char word[]);
void deleteFunction(char word[]);
int countBefore(treeNode *root, char searchKey[]);
void preOrder(treeNode *ptr);
void preOrderToFile(treeNode *ptr);
void inOrder(treeNode *ptr);
void inOrderToFile(treeNode *ptr);
void postOrder(treeNode *ptr);
void postOrderToFile(treeNode *ptr);
void printTree();
void printSearchPhase();
void printDeletePhase();

int main(void)
{
    char word[SIZE];
    int i, n, s, d;

    node = NULL;

    openFile = fopen("in.txt", "r");

    if (openFile == NULL)
        return 0;

    fscanf(openFile, "%d %d %d", &n, &s, &d);

    for (i = 0; i < n; i++)
      insertWord(word);

    outFile = fopen("out.txt", "w");

    printf("\noutfile (out.txt) written:...");

    printTree();

    printSearchPhase();
    for (i = 0; i < s; i++)
      searchWord(word);

    printDeletePhase();
    for (i = 0; i < d; i++)
      deleteWord(word);

    printTree();

    printf("\n\n");

    return 0;
}

treeNode *createNode(char *word)
{
  treeNode *temp = (treeNode*) malloc(sizeof(treeNode));
  strcpy(temp->word, word);
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

void searchFunction(char word[], treeNode **root, treeNode **location)
{
    treeNode *ptr, *temp;

    if (node == NULL)
    {
        *location = NULL;
        *root = NULL;
        return;
    }

    if (strcmp(word, node->word) == 0)
    {
        *location = node;
        *root = NULL;
        return;
    }
    if (strcmp(word, node->word) < 0)
        ptr = node->left;
    else
        ptr = node->right;

    temp = node;

    while (ptr != NULL)
    {
        if (strcmp(word, ptr->word) == 0)
        {
            *location = ptr;
            *root = temp;
            return;
        }

        temp = ptr;

        if (strcmp(word, ptr->word) <= 0)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    *location = NULL;
    *root = temp;
}

void searchWord(char word[])
{
  treeNode *temp = node;
  int check = 0;

  fscanf(openFile, "%s", word);

  while (temp != NULL)
  {
      if (strcmp(word, temp->word) == 0)
      {
          printf("\n%s: Found, Items before: %d", word, countBefore(node, word));
          fprintf(outFile, "\n%s: Found, Items before: %d", word, countBefore(node, word));
          check = 1;
          break;
      }
      if (strcmp(word, temp->word) <= 0)
          temp = temp->left;
      else
          temp = temp->right;
  }
  if (check == 0)
  {
    printf("\n%s: Not Found, Items before: %d", word, 0);
    fprintf(outFile, "\n%s: Not Found, Items before: %d", word, 0);
  }
}

void insertFunction(char word[])
{
    treeNode *root, *location, *temp;

    searchFunction(word, &root, &location);

    if (location != NULL)
        return;

    temp = createNode(word);

    if (root == NULL)
        node = temp;
    else
        if (strcmp(word, root->word) <= 0)
            root->left = temp;
        else
            root->right = temp;
}

void insertWord(char word[])
{
  fscanf(openFile, "%s", word);
  insertFunction(word);
}

void isLeaf(treeNode *root, treeNode *location)
{
    if (root == NULL)
        node = NULL;
    else
        if (location == root->left)
            root->left = NULL;
        else
            root->right = NULL;
}

void oneEmpty(treeNode *root, treeNode *location)
{
    treeNode *child;

    if (location->left != NULL)
        child = location->left;
    else
        child = location->right;

    if (root == NULL)
        node = child;
    else
        if (location == root->left)
            root->left = child;
        else
            root->right = child;
}

void noneEmpty(treeNode *root, treeNode *location)
{
    treeNode *ptr, *temp, *next, *prev;

    temp = location;

    ptr = location->right;

    while (ptr->left != NULL)
    {
        temp = ptr;
        ptr = ptr->left;
    }

    next = ptr;

    prev = temp;

    if (next->left == NULL && next->right == NULL)
        isLeaf(prev, next);
    else
        oneEmpty(prev, next);

    if (root == NULL)
        node = next;
    else
        if (location == root->left)
            root->left = next;
        else
            root->right = next;

    next->left = location->left;
    next->right = location->right;
}

void deleteFunction(char word[])
{
    treeNode *root, *location;

    if (node == NULL)
        return;

    searchFunction(word, &root, &location);

    if (location == NULL)
        return;

    if (location->left == NULL && location->right == NULL)
        isLeaf(root, location);

    if (location->left != NULL && location->right == NULL)
        oneEmpty(root, location);

    if (location->left == NULL && location->right != NULL)
        oneEmpty(root, location);

    if (location->left != NULL && location->right != NULL)
        noneEmpty(root, location);

    printf("\n%s: deleted", location->word);
    fprintf(outFile,"\n%s: deleted", location->word);
    free(location);

    return;
}

void deleteWord(char word[])
{
  fscanf(openFile, "%s", word);
  deleteFunction(word);
}

int countBefore(treeNode *root, char searchKey[])
{
  if (root == NULL)
    return 0;
  else if(strcmp(searchKey, root->word) == 0)
    return countBefore(root->left, searchKey) + countBefore(root->right, searchKey);
  else if(strcmp(searchKey, root->word) < 0)
    return countBefore(root->left, searchKey);
  else if (strcmp(searchKey, root->word) > 0)
    return 1 + countBefore(root->left, searchKey) + countBefore(root->right, searchKey);
  else
    return 0;
}

void preOrder(treeNode *ptr)
{
    if (node == NULL)
        return;

    if (ptr != NULL)
    {
        printf("%s ", ptr->word);
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

void preOrderToFile(treeNode *ptr)
{
    if (node == NULL)
        return;

    if (ptr != NULL)
    {
        fprintf(outFile, "%s ", ptr->word);
        preOrderToFile(ptr->left);
        preOrderToFile(ptr->right);
    }
}

void inOrder(treeNode *ptr)
{
    if (node == NULL)
        return;

    if (ptr != NULL)
    {
        inOrder(ptr->left);
        printf("%s ", ptr->word);
        inOrder(ptr->right);
    }
}

void inOrderToFile(treeNode *ptr)
{
    if (node == NULL)
        return;

    if (ptr != NULL)
    {
        inOrderToFile(ptr->left);
        fprintf(outFile,"%s ", ptr->word);
        inOrderToFile(ptr->right);
    }
}

void postOrder(treeNode *ptr)
{
    if (node == NULL)
        return;

    if (ptr != NULL)
    {
        postOrder(ptr->left);
        postOrder(ptr->right);
        printf("%s ", ptr->word);
    }
}

void postOrderToFile(treeNode *ptr)
{
    if (node == NULL)
        return;

    if (ptr != NULL)
    {
        postOrderToFile(ptr->left);
        postOrderToFile(ptr->right);
        fprintf(outFile,"%s ", ptr->word);
    }
}

void printTree()
{
  printf("\n\nPre Order: ");
  preOrder(node);
  printf("\nIn Order: ");
  inOrder(node);
  printf("\nPost Order: ");
  postOrder(node);

  fprintf(outFile, "\n\nPre Order: ");
  preOrderToFile(node);
  fprintf(outFile, "\nIn Order: ");
  inOrderToFile(node);
  fprintf(outFile, "\nPost Order: ");
  postOrderToFile(node);
}

void printSearchPhase()
{
  printf("\n\nSearch Phase:");
  fprintf(outFile, "\n\nSearch Phase:");
}
void printDeletePhase()
{
  printf("\n\nDelete Phase:");
  fprintf(outFile, "\n\nDelete Phase:");
}
