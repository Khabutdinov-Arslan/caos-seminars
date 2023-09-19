#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("in.txt", O_RDONLY);
    char buff[1];
    pread(fd, &buff, sizeof(buff), 7);
    write(1, buff, sizeof(buff));
    close(fd);
    return 0;
}

