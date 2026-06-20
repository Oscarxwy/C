#include<stdio.h>
#include<stdlib.h>

void countSort(int arr[], int n) 
{
    int i;
    int max = arr[0];

    // Find the maximum element in the array
    for (i = 1; i < n; i++) 
    {
        if (arr[i] > max)
            max = arr[i];
    }

    // Create count array to store count of individual elements
    int *count = (int *)calloc(max + 1, sizeof(int));

    // Store count of each element in count array
    for (i = 0; i < n; i++)
        count[arr[i]]++;

    // Update the input array with sorted elements
    int index = 0;
    for (i = 0; i <= max; i++) 
    {
        while (count[i] > 0) 
        {
            arr[index++] = i;
            count[i]--;
        }
    }

    free(count);
}

int main() 
{
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    countSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}