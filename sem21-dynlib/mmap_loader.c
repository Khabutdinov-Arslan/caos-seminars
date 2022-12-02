#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

typedef double (*func_t)(double);

int main(int argc, char** argv) {
    int input_file = open("libfoo.so", O_RDONLY);
    struct stat file_stats;
    fstat(input_file, &file_stats);
    char* content_ptr = mmap(NULL, file_stats.st_size, PROT_READ | PROT_EXEC | PROT_WRITE, MAP_PRIVATE, input_file, 0);
    func_t func = (func_t)(content_ptr + 0x10f9);
    double argument;
    while (scanf("%lf", &argument) != EOF) {
        printf("%.3f\n", func(argument));
    }
    munmap(content_ptr, file_stats.st_size);
    close(input_file);
}
