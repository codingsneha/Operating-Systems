#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x) {
            return mid;
        }

        if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <element_to_search> <sorted_element1> <sorted_element2> ... <sorted_elementN>\n", argv[0]);
        return 1;
    }

    int elementToSearch = atoi(argv[1]);
    int n = argc - 2;
    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 2]);
    }

    int result = binarySearch(arr, 0, n - 1, elementToSearch);

    if (result != -1) {
        printf("Element found at index %d\n", result);
        free(arr);
        return 0;
    } else {
        printf("Element not found\n");
        free(arr);
        return 1;
    }
}