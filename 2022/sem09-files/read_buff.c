#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int read_buff(int fd, char* buff, size_t buff_size)
{
    size_t read_buff_size = 0;
    while (read_buff_size < buff_size) {
        size_t read_during_iteration =
            read(fd, buff + read_buff_size, buff_size - read_buff_size);
        read_buff_size += read_during_iteration;
        if (read_during_iteration == 0) {
            return read_buff_size;
        }
        if ((read_during_iteration < 0) && (errno != EINTR) && (errno != EAGAIN)) {
            return -1;
        }
    }
    return read_buff_size;
}

int main() {
    const size_t BUFF_SIZE = 4096;
    char buffer[BUFF_SIZE];
    int read_count = read_buff(0, buffer, BUFF_SIZE);
    printf("Read %d", read_count);
    return 0;
}
