#include <stdio.h>
#include <stdint.h>

uint64_t A;
extern uint64_t R;

extern void calculate();

int main(){
    scanf("%llu", &A);
    calculate();
    printf("%lu\n", R);
}
