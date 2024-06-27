#include<stdio.h>
#include<stdlib.h>


void swap(int *arr, int index1, int index2){
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;

}
void heapify(int * arr, int n,int i){
    int largest  = i;
    int left = i*2;
    int right = i*2+1;

    if(left<n&&arr[largest]<arr[left]){
        largest = left;
    }
    if(right<n&&arr[largest]<arr[right]){
        largest = right;
    }

    if(largest!=i){
        swap(arr,largest,i);
        heapify(arr, n, largest);
    }
}

void heapsort(int *arr, int n){
    for(int i = n/2;i>=0;i--){
        heapify(arr, n, i);
    }

    int i = n;

    while(i>0){
        swap(arr,0 ,i);
        heapify(arr, i, 0);
        i--;

    }
}

void printArray(int*arr,int n){
    printf("\n");
    for(int i = 0;i<n;i++){
        printf("%d,",arr[i]);
    }
        printf("\n");
}

int main(){
    int arr[] = {7,3,5,2,6,7,8,5,6,7,9,10};
    printArray(arr, 11);
    heapsort(arr, 11);
    printArray(arr, 11);
}