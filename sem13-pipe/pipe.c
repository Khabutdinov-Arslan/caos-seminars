#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int pipe_out[2];
    pipe(pipe_out);

    pid_t pid = fork();

    if (pid == 0) {
        // child will write
        close(pipe_out[0]);
        dup2(pipe_out[1], 1);
        close(pipe_out[1]);

        execlp(argv[1], argv[1], NULL);
    } else {
        // parent will read
        close(pipe_out[1]);
        dup2(pipe_out[0], 0);
        close(pipe_out[0]);

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
