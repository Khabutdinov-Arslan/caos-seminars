#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Hello from child with pid %d!\n", getpid());
        return 179;
    } else {
        int status;
        waitpid(pid, &status, 0);
        printf("Child exited with code %d\n", WEXITSTATUS(status));
        printf("Hello from parent!\n");
    }
}