#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    size_t BUFF_SIZE = 4096;
    char* shell_intro = "my_shell> ";
    printf("%s", shell_intro);

    char* buff = malloc(BUFF_SIZE);
    size_t read;
    while((read = getline(&buff, &BUFF_SIZE, stdin)) != -1){
        size_t MAX_ARGS = 10;
        char* args[MAX_ARGS];
        for (int i = 0; i < MAX_ARGS; i++) {
            args[i] = NULL;
        }
        char* pos;
        pos = strtok(buff, " \n");
        int argc = 0;
        while (pos != NULL) {
            args[argc] = pos;
            ++argc;
            pos = strtok(NULL, " \n");
        }

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Can't spawn child: ");
        } else {
            waitpid(pid, NULL, 0);
            printf("%s", shell_intro);
        }
    }

    return 0;
}