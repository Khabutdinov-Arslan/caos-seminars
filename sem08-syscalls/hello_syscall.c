#include <sys/syscall.h>

long syscall(long number, ...);

void _start()
{
    char* msg = "Hello, World!";
    syscall(/*syscall_number=*/SYS_write, /*fd=*/1, /*string=*/msg, /*length=*/13);
    syscall(SYS_exit, 0);
}
