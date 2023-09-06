#include "stdio.h"

extern int get(int* arr, int idx);

int main() {
    int arr[3] = {1, -7, 9};
    int res = get(arr, 1);
    printf("%d\n", res);
}