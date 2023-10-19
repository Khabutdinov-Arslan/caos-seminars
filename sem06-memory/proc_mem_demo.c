#define _LARGEFILE64_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    char mem_file_name[_SC_PAGE_SIZE];
    int pid = atoi(argv[1]);
    uint64_t offset = strtoull(argv[2], NULL, 16);
    sprintf(mem_file_name, "/proc/%d/mem", pid);

    int mem_fd = open(mem_file_name, O_RDONLY);
    if (mem_fd == -1) {
        perror("Can't open process memory: ");
        return 0;
    }
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    waitpid(pid, NULL, 0);

    lseek64(mem_fd, offset, SEEK_SET);
    char buf[_SC_PAGE_SIZE];
    int read_bytes_cnt = read(mem_fd, buf, _SC_PAGE_SIZE);
    if (read_bytes_cnt == -1) {
        perror("Can't read from memory: ");
        return 0;
    }

    printf("Read bytes: %d\n", read_bytes_cnt);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    printf("%s\n", buf);

    return 0;
}
