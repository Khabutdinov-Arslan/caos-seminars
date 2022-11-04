#include <sys/syscall.h>

long syscall(long number, ...);

void _start() {
    const int size = 8 * 10;
    int* data_start = (void*)syscall(SYS_brk, 0);
    int* data_end = (void*)syscall(SYS_brk, (int*)data_start + size);

    data_start[0] = 0;
    int len = data_end - data_start;
    for (int i = 1; i < len; ++i) {
        data_start[i] = data_start[i - 1] + 1;
    }
    char msg = ('0' + (data_start[len - 1]) % 10);
    syscall(SYS_write, 1, &msg, 1);

    syscall(SYS_exit, 0);
}
