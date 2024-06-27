#include <stdio.h>
#include <stdlib.h>

void print_array(int **array, int n)
{
    int **arr = array;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

void take_input(int **array, int n)
{
    int **arr = array;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\nenter element on index [%d][%d]", i, j);
            scanf("%d", *(arr + i) + j);
        }
    }

    printf("\n");
}

void swap(int **arr, int n)
{
    int tmp;
    for (int i = 0; i < n; i++)
    {

        tmp = *(*(arr + i) + i);
        *(*(arr + i) + i) = *(*(arr + i) + (n - i - 1));
        *(*(arr + i) + (n - 1 - i)) = tmp;
    }
}

void rotate(int **arr, int n)
{
    int tmp1, tmp2, tmp3, tmp4;

    int k = n / 2;

    for (int i = 0; i < k; i++)
    {
        for (int j = i; j < n - i - 1; j++)
        {

            // tmp1 = arr[i][j];
            tmp1 = *(*(arr + i) + j);

            // tmp2 = arr[j][n - i - 1];

            tmp2 = *(*(arr + j) + (n - i - 1));

            // tmp3 = arr[n - 1 - i][n - 1 - j];

            tmp3 = *(*(arr + n - 1 - i) + n - 1 - j);

            // tmp4 = arr[n - j - 1][i];

            tmp4 = *(*(arr + n - j - 1) + i);

            arr[i][j] = tmp4;
            arr[j][n - i - 1] = tmp1;
            arr[n - 1 - i][n - 1 - j] = tmp2;
            arr[n - j - 1][i] = tmp3;

            
        }
    }
}
int main()
{
    int n;
    printf("enter the size : ");
    scanf("%d", &n);
    int **arr = (int **)malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * n);
        printf("index %d created", i);
    }

    take_input(arr, n);
    print_array(arr, n);
    // swap(arr,n);
    // print_array(arr,n);
    rotate(arr, n);
    print_array(arr, n);
}