#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *dir_name = (argc > 1) ? argv[1] : getcwd(malloc(PATH_MAX), PATH_MAX);
    DIR* dir = opendir(dir_name);
    for (struct dirent* cur_entry = readdir(dir); cur_entry; cur_entry = readdir(dir)){
        printf("%s\n", cur_entry->d_name);
    }
    closedir(dir);
    return 0;
}
