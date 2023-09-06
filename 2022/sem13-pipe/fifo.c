#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        mkfifo("./fifo_demo", 0644);
        int fd = open("./fifo_demo", O_WRONLY);
        dup2(fd, 1);
        close(fd);
        execlp(argv[1], argv[1], NULL);
    } else {
        // parent will read
        sleep(1); // not the best way to sync, but
        int fd = open("./fifo_demo", O_RDONLY);
        dup2(fd, 0);
        close(fd);

        int total_read = 0;
        char buffer[4096];
        int current_read;
        while ((current_read = read(0, buffer, sizeof(buffer))) > 0) {
            total_read += current_read;
        }
        printf("%d\n", total_read);
        waitpid(pid, NULL, 0);
    }
}
