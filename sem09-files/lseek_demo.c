#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("in.txt", O_RDONLY);
    lseek(fd, 7, SEEK_SET);
    char buff[1];
    read(fd, &buff, 1);
    write(1, buff, 1);
    close(fd);
    return 0;
}

