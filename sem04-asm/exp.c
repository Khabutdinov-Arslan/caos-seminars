#include <stdio.h>

extern double my_exp();

int main() {
    double x;
    scanf("%lf", &x);
    printf("%lf\n", my_exp(x));
    return 0;
}
