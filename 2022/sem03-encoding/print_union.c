#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <inttypes.h>

typedef union {
    double double_val;
    struct {
        uint64_t mantissa_val : 52;
        uint64_t exp_val : 11;
        uint64_t sign_val : 1;
    };
} double_parser_t;

int main() {
    double_parser_t op = {.double_val = -130.0};
    printf("F = %f\n", op.double_val);
    printf("S = %d\n", op.sign_val);
    printf("E = %d\n", op.exp_val);
    printf("M = %lld\n", (long long unsigned int)op.mantissa_val);
    return 0;
}