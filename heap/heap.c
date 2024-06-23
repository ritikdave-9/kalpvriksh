#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct node {
  int data;
  struct node *left;
  struct node *right;
} node;

typedef struct heap {
  int *arr;
  int index;
  int size;
} heap;

heap *createHeap(int size) {
  heap *newheap = (heap *)malloc(sizeof(heap));

  newheap->arr = (int *)calloc(size, sizeof(int));
  newheap->index = 0;
  newheap->size = size;
  return newheap;
}

int isFull(heap *hp) {
  if (hp->index == hp->size) {
    return 1;
  }

  return 0;
}

void swap(int *arr, int index1, int index2) {
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}

void insert(heap *hp, int data) {
  if (isFull(hp)) {
    printf("heap is full\n");
    return;
  }
  hp->index++;
  int index = hp->index;
  hp->arr[index] = data;

  while (index > 1 && hp->arr[index] > hp->arr[index / 2]) {
    swap(hp->arr, index, index / 2);
    index = index / 2;
  }
}

void deleteHp(heap* hp){
    swap(hp->arr,1,hp->index);
    hp->arr[hp->index] = 0;
    hp->index--;
    int index = 1;

    while(index<hp->index){
        int left = index*2;
        int right = index*2+1;

        int gt = (hp->arr[left]>hp->arr[right])?left:right;

        if(hp->arr[index]<hp->arr[gt]){
            swap(hp->arr, index, gt);
            index = gt;
        }
        else{
            break;
        }
    }
}
void deleteHpAValue(heap* hp,int value){
    int index = -1;

    for(int i = 1;i<=hp->index;i++){
        if(hp->arr[i]==value){
            index = i;
            break;
        }
        
    }
    if(index==-1){
        printf("Element Not Present \n");
        return;

    }

    swap(hp->arr,index,hp->index);
    hp->arr[hp->index] = 0;
    hp->index--;

    while(index<hp->index){
        int left = index*2;
        int right = index*2+1;

        int gt = (hp->arr[left]>hp->arr[right])?left:right;

        if(hp->arr[index]<hp->arr[gt]){
            swap(hp->arr, index, gt);
            index = gt;
        }
        else{
            break;
        }
    }
}


void printHeap(heap *hp) {
  printf("\n");

  for (int i = 1; i < hp->index + 1; i++) {
    printf("%d, ", hp->arr[i]);
  }
  printf("\n");
}

int main() {
  heap *hp = createHeap(100);
  insert(hp, 10);
  insert(hp, 1);
  insert(hp, 19);
  insert(hp, 11);

  deleteHp(hp);
  insert(hp, 20);

  printHeap(hp);
  deleteHpAValue(hp,1);
  printHeap(hp);
  deleteHpAValue(hp,11);
  printHeap(hp);
}