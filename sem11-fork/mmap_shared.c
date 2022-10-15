#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
    char* content_ptr = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    strcpy(content_ptr, "Hello");
    pid_t pid = fork();
    if (pid == 0) {
        printf("Parent says: %s!\n", content_ptr);
        strcpy(content_ptr, "Hola");
    } else {
        int status;
        waitpid(pid, &status, 0);
        printf("Child says: %s!\n", content_ptr);
    }
    return 0;
}
