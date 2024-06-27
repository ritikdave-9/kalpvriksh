#include<stdio.h>

#include<stdlib.h>
#include <string.h>


typedef  struct heap{
    char **arr;
    int index;
    int size;
}heap;

heap* createHeap(int size){
    heap* newheap = (heap*)malloc(sizeof(heap));
    newheap->arr = (char**)calloc(size, sizeof(char*));
    newheap->index = -1;
    newheap->size = size;
    return newheap;
}

void swap(char** arr, int index1, int index2){
    char * temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;

}

void insertHeap(heap* hp, char* str){
    if(hp->index>=hp->size-1){
        printf("heap is full");

        return;
    }

    hp->index++;
    int index = hp->index;

    hp->arr[index] = strdup(str);

    while(index>0&&strcmp(hp->arr[index],hp->arr[(index-1)/2])<0){
        swap(hp->arr, index, (index-1)/2);
        index = (index-1)/2;
    }



}

void printHeap(heap* hp){

    printf("\n");
    for(int i = 0;i<=hp->index;i++){
        printf("%s , ",hp->arr[i]);
    }
    printf("\n");
}

int main(){
    heap* hp = createHeap(100);
    // char ch1[] = "hello";
    insertHeap(hp, "hello");
        insertHeap(hp, "abc");
    insertHeap(hp, "baby");
    insertHeap(hp, "bbc");

    printHeap(hp);
}