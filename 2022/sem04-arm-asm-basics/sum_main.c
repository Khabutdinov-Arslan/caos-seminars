#include <stdio.h>

extern int sum(int a, int b);

int main(){
    int a;
    int b;
    scanf("%d %d", &a, &b);
    int c = sum(a, b);
    printf("%d\n", c);
}