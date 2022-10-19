#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    dup2(fd, 1);
    close(fd); // now we can close original descriptor
    printf("Hello, world!");
    return 0;
}
