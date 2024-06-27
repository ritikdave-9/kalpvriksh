#include <stdio.h>

#include <stdlib.h>
#include <strings.h>

typedef struct heap {
  int *arr;
  int index;
  int size;
} heap;

heap *createHeap(int size) {
  heap *newhp = (heap *)malloc(sizeof(heap));

  newhp->arr = (int *)calloc(size, sizeof(int));

  newhp->index = -1;

  newhp->size = size;
  return newhp;
}

void swap(int *arr, int index1, int index2) {
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}

void insertHeap(heap *hp, int data) {
  if (hp->index == hp->size - 1) {

    printf("heap is full");
    return;
  }
  hp->index++;
  int index = hp->index;

  hp->arr[index] = data;

  while (index >= 0 && hp->arr[index] < hp->arr[(index - 1) / 2]) {
    swap(hp->arr, index, (index - 1) / 2);
    index = index / 2;
  }

  return;
}

void printHeap(heap *hp) {
  printf("\n");
  for (int i = 0; i <= hp->index; i++) {
    printf("%d, ", hp->arr[i]);
  }
  printf("\n");
}

void heapifyutils(int *arr, int n, int pos) {
  int largest = pos;
  int left = pos * 2;
  int right = pos * 2 + 1;

  if (left < n && arr[largest] < arr[left]) {

    largest = left;
  }
  if (right < n && arr[largest] < arr[right]) {
    largest = right;
  }

  if (largest != pos) {
    swap(arr, largest, pos);
    heapifyutils(arr, n, largest);
  }
}

void heapify(int *arr, int n) {

  for (int i = n / 2; i >= 0; i--) {
    heapifyutils(arr, n, i);
  }
}

void printArray(int *arr, int n) {
  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}
void heapSort(int *arr, int n) {

  heapify(arr, n);

  for (int i = n - 1; i >= 0; i--) {
    swap(arr, 0, i);
    heapifyutils(arr, i, 0);
  }
}

int k_largestElement(int *arr, int n, int k) {
  int ans;
  heapify(arr, n);

  for (int i = 0; i < k; i++) {

    heapifyutils(arr + i, n, 0);
  }
}
int main() {
  int arr[] = {56, 23, 78, 45, 21, 43, 80, 28, 23};
  heapify(arr, 9);
  heapSort(arr, 9);
  printArray(arr, 9);
}