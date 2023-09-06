#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char file_name[PATH_MAX];
    size_t regular_count = 0;
    size_t symlink_count = 0;
    size_t executable_count = 0;
    struct stat file_stats;
    while (fgets(file_name, sizeof(file_name), stdin)) {
        for (size_t i = 0; i < sizeof(file_name); i++) {
            if (file_name[i] == '\n') {
                file_name[i] = '\0';
                break;
            }
        }
        if (lstat(file_name, &file_stats) != -1) {
            if (S_ISREG(file_stats.st_mode)) {
                ++regular_count;
            }
            if (S_ISLNK(file_stats.st_mode)) {
                ++symlink_count;
            }
        }
        if (access(file_name, X_OK)) {
            ++executable_count;
        }
    }
    printf("Regular files count = %lu\nSymbolic links count = %lu\nExecutable count = %lu\n", regular_count, symlink_count, executable_count);
    return 0;
}
