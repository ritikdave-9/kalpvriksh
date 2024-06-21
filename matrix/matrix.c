#include<stdio.h>
#include<stdlib.h>

int ** createMatrix(int m , int n){
    int ** arr = (int **)calloc(m, sizeof(int*));

    for(int i = 0;i<m;i++){
        arr[i] = (int *)calloc(n, sizeof(int));
    }
    return arr;

}

void 


