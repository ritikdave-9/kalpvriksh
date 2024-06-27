#include <stdio.h>

#include <stdlib.h>

typedef struct heap {
  int *arr;
  int index;
  int size;

} heap;

heap *createHeap(int size) {
  heap *newheap = (heap *)malloc(sizeof(heap));

  newheap->arr = (int *)calloc(size, sizeof(int));

  newheap->size = size;
  newheap->index = -1;
  return newheap;
}

void swap(int *arr, int index1, int index2) {
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}

void insert_max_heap(heap *hp, int data) {
  if (hp->index == hp->size - 1) {
    printf("heap full");

    return;
  }

  hp->index++;
  int index = hp->index;

  hp->arr[index] = data;

  while (index > 0 && hp->arr[index] > hp->arr[(index - 1) / 2]) {

    swap(hp->arr, index, (index - 1) / 2);
    index = (index - 1) / 2;
  }
}

void insert_min_heap(heap *hp, int data) {
  if (hp->index == hp->size - 1) {
    printf("heap full");

    return;
  }

  hp->index++;
  int index = hp->index;

  hp->arr[index] = data;

  while (index > 0 && hp->arr[index] < hp->arr[(index - 1) / 2]) {

    swap(hp->arr, index, (index - 1) / 2);
    index = (index - 1) / 2;
  }
}

void printHeap(heap *hp) {

  printf("\n");
  for (int i = 0; i <= hp->index; i++) {

    printf("%d, ", hp->arr[i]);
  }
  printf("\n");
}

int deleteMaxHeap(heap *hp) {
  int data = hp->arr[0];
  swap(hp->arr, hp->index, 0);

  hp->arr[hp->index] = 0;
  hp->index--;

  int index = 0;

  while (index < hp->index) {

    int left = index * 2 + 1;
    int right = index * 2 + 2;

    int gt = (hp->arr[left] > hp->arr[right]) ? left : right;

    if (hp->arr[gt] > hp->arr[index]) {
      swap(hp->arr, gt, index);
      index = gt;
    } else {
      break;
    }
  }

  return data;
}
int deleteMinHeap(heap *hp) {
  int data = hp->arr[0];
  swap(hp->arr, hp->index, 0);

  hp->arr[hp->index] = 0;
  hp->index--;

  int index = 0;

  while (index < hp->index) {

    int left = index * 2 + 1;
    int right = index * 2 + 2;

    int gt = (hp->arr[left] < hp->arr[right]) ? left : right;

    if (hp->arr[gt] < hp->arr[index]) {
      swap(hp->arr, gt, index);
      index = gt;
    } else {
      break;
    }
  }

  return data;
}

void insert(heap *maxheap, heap *minheap, int data) {

  if (maxheap->index == -1 || data <= maxheap->arr[0]) {
    insert_max_heap(maxheap, data);
  } else {
    insert_min_heap(minheap, data);
  }

  if (maxheap->index > minheap->index + 1) {
    insert_min_heap(minheap, deleteMaxHeap(maxheap));
  } else if (maxheap->index < minheap->index ) {
    insert_max_heap(maxheap, deleteMinHeap(minheap));
  }
}

int median(heap *maxheap, heap *minheap) {
  if (maxheap->index == minheap->index) {
    return (maxheap->arr[0] + minheap->arr[0]) / 2;
  }

  else {
    return maxheap->arr[0];
  }
}

int main() {
  heap *mxheap = createHeap(100);
  heap *minheap = createHeap(100);

  insert(mxheap, minheap, 2);
  printf("%d\n", median(mxheap, minheap));

  insert(mxheap, minheap, 3);

  printf("%d\n", median(mxheap, minheap));

  insert(mxheap, minheap, 5);

  printf("%d\n", median(mxheap, minheap));
  insert(mxheap, minheap, 7);

  printf("%d\n", median(mxheap, minheap));

  insert(mxheap, minheap, 10);

  printf("%d\n", median(mxheap, minheap));

  

}