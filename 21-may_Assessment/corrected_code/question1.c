#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int n)
{
    int *temp = arr;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *temp);
            temp++;
        }
        printf("\n");
    }
}

void inputArray(int *arr, int n)
{
    int *temp = arr;

    printf("enter %d elements\n", n * n);

    for (int i = 0; i < n * n; i++)
    {
        scanf("%d", temp++);
    }
}

void swapPattern(int *arr, int n)
{
    int *temp = arr;
    int *prev = arr;
    int tempdata;

    for (int i = 0; i < n ; i++)
    {
        prev = temp + i;
        

        temp = temp + n-i-1;
        tempdata = *temp;
        *temp = *prev;
        *prev = tempdata;
        // temp = arr;
        temp = arr + n*(i+1);
    }

}

int main()
{
    int n;
    printf("enter size of 2D array : ");
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n * n);
    inputArray(arr, n);

    printArray(arr, n);
    swapPattern(arr,n);
    printf("=================\n\n");
    printArray(arr, n);
}