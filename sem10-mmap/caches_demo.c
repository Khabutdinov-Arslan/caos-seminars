#include <stdint.h>
#include <stdio.h>
#include <time.h>

enum { PAD_SIZE = 7 };
// 150 and 250 practically no difference
// 10 and 30 no difference
enum { EL_COUNT = 10000000 };

typedef struct el{
    uint64_t pad[PAD_SIZE];
    uint64_t value;
} el;

el arr[EL_COUNT];

int main(){
    for (uint64_t i = 0; i < EL_COUNT; i++) {
        arr[i].value = (i * i - i + 179) % 444;
    }
    uint64_t sum = 0;
    clock_t tbegin = clock();
    for (uint64_t i = 0; i < EL_COUNT; i++) {
        sum += arr[i].value;
    }
    clock_t tend = clock();
    printf("Sum is %lu \n", sum);
    double time_spent = (double)(tend - tbegin) / CLOCKS_PER_SEC;
    printf("Time spent is %.6f \n", time_spent);
    return 0;
}