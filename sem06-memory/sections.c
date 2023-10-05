#include <stdio.h>

int global_var; // bss

int main() { // text
    static int static_var = 5; // data
    int local_var; // stack
    printf("global_var %p\n", &global_var);
    printf("static_var %p\n", &static_var);
    printf("local_var  %p\n", &local_var);
    printf("main       %p\n", &main);
}
