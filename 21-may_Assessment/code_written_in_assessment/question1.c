#include<stdio.h>
#include <stdlib.h>


void swap(int * mainarr, int n){
    int * arr = mainarr;
    int temp;
    int i = 0;
    

    while(i<n){
        
            int * arrTemp = arr;

            temp = *arr;

            arr = arr+ n - i;

            *arrTemp = *arr;
            *arr = temp;
            arr = arr+ i+1;

            i++;

}

void inputarr(int * arr, int n){
    int i = 0;
    while(i<n*n){
        scanf("%d",*arr);
        arr++;
        i++;
    }
}

void printarr(int * arr, int n){
    int i = 0;
    int j = 0;
    while(i<n){
        while(j<n){
            printf("%d",*arr);
            arr++;
            j++;
        }
        printf("\n");
        i++;

    }
}

int main(){
    int n;
    printf("enter n");
    scanf("%d",n);

    int * arr = (int*)malloc(sizeof(int)*n*n);
    inputarr(arr,n);
    printarr(arr,n);
    swap(arr,n);
    printarr(arr,n);



return 0;

    



}

}