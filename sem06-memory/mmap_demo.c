#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
    int input_file = open(argv[1], O_RDONLY);
    struct stat file_stats;
    fstat(input_file, &file_stats);
    char* content_ptr = mmap(NULL, file_stats.st_size, PROT_READ, MAP_PRIVATE, input_file, 0);
    posix_madvise(content_ptr, file_stats.st_size, POSIX_MADV_SEQUENTIAL); // compare POSIX_MADV_RANDOM with POSIX_MADV_SEQUENTIAL

    size_t cnt[10];
    memset(cnt, 0, sizeof(cnt));
    for (size_t i = 0; i < file_stats.st_size; i++) {
        cnt[content_ptr[i] - '0']++;
    }

    for (int i = 0; i < 10; i++) {
        printf("%lu ", cnt[i]);
    }
    printf("\n");

    struct rusage resource_usage;
    getrusage(RUSAGE_SELF, &resource_usage);
    printf("Minor page faults: %ld\n", resource_usage.ru_minflt);
    printf("Major page faults: %ld\n", resource_usage.ru_majflt);
    
    pause();

    munmap(content_ptr, file_stats.st_size);
    close(input_file);
}
