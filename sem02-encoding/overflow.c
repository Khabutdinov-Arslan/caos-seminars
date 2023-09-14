#include <stdint.h>
#include <stdio.h>

int main() {
    int32_t n = (1 << 31) - 1;
    n += 1;
    printf("%d\n", n);
}