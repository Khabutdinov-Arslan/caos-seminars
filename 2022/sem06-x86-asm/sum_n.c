#include <stdio.h>

extern int sum(int n);

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", sum(n));
}
