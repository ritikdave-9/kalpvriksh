#include <stdio.h>
#include <stdlib.h>

#include<string.h>

// Given function
int fun(int a, int b) {
    return (a + b) - 2 * (a & b);
}

// Optimized triplet function using sorting and two-pointer technique
int triplet(int *arr, int n) {
    int ans = 0;
    
    // Sort the array
    qsort(arr, n, sizeof(int), (int (*)(const void *, const void *)) strcmp);

    // Iterate over each element
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;

        // Use two-pointer technique
        while (left < right) {
            ans += fun(arr[i], fun(arr[left], arr[right]));

            // Move pointers
            left++;
            right--;
        }
    }
    return ans;
}



int main() {
    int n;
    scanf("%d", &n);
    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%d", triplet(arr, n));
}
