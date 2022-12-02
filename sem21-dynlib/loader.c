#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*func_t)(double);

int main(int argc, char* argv[])
{
    if (argc != 3){
        fprintf(stderr, "There must be 2 arguments: library file and fucntion name");
        exit(1);
    }
    void* lib = dlopen(argv[1], RTLD_NOW);
    if (! lib) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        exit(1);
    }
    void * entry = dlsym(lib, argv[2]);
    if (! entry) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        exit(1);
    }
    func_t func = entry;
    double argument;
    while (scanf("%lf", &argument) != EOF) {
        printf("%.3f\n", func(argument));
    }
    dlclose(lib);
}
