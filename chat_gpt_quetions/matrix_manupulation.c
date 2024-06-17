#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **arr, int n)
{
    int **temp = arr;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(*(temp + i) + j));
        }
        printf("\n");
    }
}

void getMatrix(int **arr, int n)
{
    int **temp = arr;

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            scanf("%d", *(temp + i) + j);
        }
    }
}

void rotate(int **arr, int n)
{
    int **temp = arr;

    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n - i - 1; j++)
        {

            int temp = *(*(arr + i) + j);
            *(*(arr + i) + j) = *(*(arr + n - j - 1) + i);
            *(*(arr + n - j - 1) + i) = *(*(arr + n - i - 1) + n - j - 1);
            *(*(arr + n - i - 1) + n - j - 1) = *(*(arr + j) + n - i - 1);
            *(*(arr + j) + n - i - 1) = temp;
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int **arr = (int **)malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * n);
    }

    getMatrix(arr, n);
    printMatrix(arr, n);
    rotate(arr, n);
    printMatrix(arr, n);
    free(arr);
}