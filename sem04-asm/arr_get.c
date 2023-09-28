#include <stdio.h>

extern int get(int* arr, int idx);

int main() {
    int arr[3] = {1, 7, 9};
    printf("%d\n", get(arr, 1));
}
