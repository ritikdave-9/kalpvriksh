#include <stdio.h>
#include <stdlib.h>

void input_arr(int **arr, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", (*(arr + i) + j));
        }
    }
    if (m > n)
    {
        for (int i = 0; i < m - n; i++)
        {
            for (int j = 0; i < m; j++)
            {

                arr[n + i][j] = 0;
            }
        }
    }
    if (m < n)
    {
        for (int i = 0; i < m - n; i++)
        {
            for (int j = 0; i < m; j++)
            {

                arr[j][n + i] = 0;
            }
        }
    }
}
void print_arr(int **arr, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

void transpose(int **arr, int m, int n)
{
    int k;

    if (m < n)
    {
        k = m;
    }
    else
    {
        k = n;
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {

            int temp = *(*(arr + i) + j);
            *(*(arr + i) + j) = *(*(arr + j) + i);
            *(*(arr + j) + i) = temp;
        }
    }

    if (m < n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = k; j < n; j++)
            {
                

                *(*(arr+j)+i) = *(*(arr+i)+j);
                *(*(arr+i)+j)=  0;
            }
        }
    }
    if (m > n)
    {
        for (int i = k; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                

                *(*(arr+i)+j) = *(*(arr+j)+i);
                *(*(arr+j)+i)=  0;
            }
        }
    }
}

int main()
{
    int m, n;

    scanf("%d%d", &m, &n);

    int k = (m > n) ? m : n;

    int **arr = (int **)malloc(sizeof(int *) * k);

    if(arr==NULL){
        printf("unable to locate memory ");
        return 0;
    }
    for (int i = 0; i < k; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * k);
        if(arr[i]==NULL){
        printf("unable to locate memory ");
        return 0;
    }

    }

    input_arr(arr, m, n);
    print_arr(arr, m, n);
    transpose(arr, m, n);
    print_arr(arr, n, m);
    for (int i = 0; i < k; i++)
    {
        free(arr[i]);
        return 0;
    }
    free(arr);
}