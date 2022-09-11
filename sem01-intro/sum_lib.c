#include <stdio.h>

#include "sum_lib.h"

int main() {
    int a;
    int b;
    scanf("%d", &a);
    scanf("%d", &b);
    int c = sum(a, b);
    printf("%d", c);
}