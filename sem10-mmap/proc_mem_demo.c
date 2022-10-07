#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    const size_t BUFF_SIZE = 4096;
    char mem_file_name[BUFF_SIZE];
    int pid = atoi(argv[1]);
    int offset = atoi(argv[2]);
    sprintf(mem_file_name, "/proc/%d/mem", pid);
    int mem_fd = open(mem_file_name, O_RDONLY);
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    waitpid(pid, NULL, 0);
    lseek(mem_fd, offset, SEEK_SET);
    char buf[BUFF_SIZE];
    read(mem_fd, buf, _SC_PAGE_SIZE);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    printf("%s", buf);
    return 0;
}