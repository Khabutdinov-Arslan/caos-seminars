#include <stdio.h>

int get(int *a, int i) {
    return a[i];
}

int main() {
    int a[10];
    printf("%d\n", get(a, 2));
    printf("%d\n", a[27]);
    printf("%d\n", a[2007]);
    printf("%d\n", get(a, 4007));
}