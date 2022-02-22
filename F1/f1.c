/* COP 3502C Final Term Assignment 1
This program is written by: Anthony Galbo */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct point
{
  int x, y;
}point;

void merge(point arr[], int l, int m, int r);
void mergeSort(point arr[], int l, int r);
void binarySearch(point arr[], point input, int n);

int main(void)
{
  FILE *openFile, *outFile;
  int i, n;
  point arr[SIZE], input;

  openFile = fopen("in.txt", "r");

  fscanf(openFile, "%d", &n);

  for(i = 0; i < n; i++)
    fscanf(openFile, "%d %d", &arr[i].x, &arr[i].y);

  mergeSort(arr, 0, n - 1);

  outFile = fopen("out.txt", "w");

  for(i = 0; i < n; i++)
    fprintf(outFile, "%d %d\n",arr[i].x, arr[i].y);

  fclose(outFile);

  printf("\nSorted and output written\n");

  while(input.x != -999 && input.y != -999)
  {
    printf("Search input (x y): ");
    scanf("%d %d", &input.x, &input.y);
    binarySearch(arr, input, n);
  }

  return 0;
}

void merge(point arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  point left[n1], right[n2];

  for(i = 0; i < n1; i++)
    left[i] = arr[l + i];
  for(j = 0; j < n2; j++)
    right[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;

  while(i < n1 && j < n2)
  {
    if(left[i].x < right[j].x || (left[i].x == right[j].x && left[i].y < left[i].y))
      arr[k] = left[i++];
    else
      arr[k++] = right[j++];
  }

  while(i < n1)
    arr[k++] = left[i++];

  while(j < n2)
    arr[k++] = right[j++];
}

void mergeSort(point arr[], int l, int r)
{
  if(l < r)
  {
    int m = (l + r)/2;

    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);

    merge(arr, l, m, r);
  }
}

void binarySearch(point arr[], point input, int n)
{
  int l, r, mid;

  l = 0;
  r = n - 1;

  while(l < r)
  {
    mid = (l + r)/2;

     if(arr[mid].x < input.x || (arr[mid].x == input.x && arr[mid].y < input.y))
       l = mid + 1;
     else
       r = mid;
  }

  if(input.x == -999 && input.y == -999)
  {
    printf("Output: exit\n\n");
    return;
  }
  else if(arr[l].x == input.x && arr[l].y == input.y)
    printf("Output: Found at record %d\n", l+1);
  else
    printf("Output: Not found\n");
}
