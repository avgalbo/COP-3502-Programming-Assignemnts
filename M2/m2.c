/* COP 3502C Midterm Assignment Two
This program is written by: Anthony Galbo */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *next;
}node;

node *createNode(int data);
void survive(node *root, int k);

node *head = NULL, *t = NULL;

int main (void)
{
  node *temp;
  int n, k, i;
  
      printf("Enter input for n: ");
      scanf("%d", &n);
      printf("Enter input for k: ");
      scanf("%d", &k);

      for(i = 1; i <= n; i++)
      {
              temp = createNode(i);

              if(head == NULL)
              {
                      head = temp;
                      temp->next = head;
              }
              else
              {
                      t = head;

                      while(t->next != head)
                          t = t->next;

                      t->next = temp;
                      temp->next = head;
              }
      }//end of for loop

        printf("\nPrison circle is: ");
        t = head;

        while(t->next != head)
        {
          printf("%d ", t->data);
          t = t->next;
        }
        printf("%d", t->data);
        printf("\nAlgorithm for execution: ");
        survive(head, k);

  return 0;
}// end of main

node *createNode(int data)
{
  node *temp;
  temp = (node*) malloc(sizeof(node));

  if(temp == NULL)
    return NULL;

  temp->data = data;
  temp->next = NULL;

  return temp;
}

void survive(node *head, int k)
{
      node *temp;
      int i;

      while(head->next != head)
      {
          for(i = 1; i < k; i++)
          {
              temp = head;
              head = head->next;
          }

          temp->next = head->next;
          printf("%d ",head->data);
          head = temp->next;
      }
      printf("\nThe position number who will survive is: #%d\n\n",head->data);
}
