#include <stdio.h>
#include <unistd.h>

#include <sys/eventfd.h>

int main() {
    uint64_t terminate_num = 42;
    int efd = eventfd(0, 0);
    if (efd == -1) {
        perror("Can't create eventfd");
    }
    pid_t pid = fork();
    if (pid == 0) {
        for (int i = 1; i <= 10; i++) {
            uint64_t num = i * i;
            write(efd, &num, sizeof(num));
            sleep(1);
        }
        write(efd, &terminate_num, sizeof(terminate_num));
    } else {
        while (1) {
            uint64_t num;
            int read_bytes = read(efd, &num, sizeof(num));
            if (read_bytes < 0) {
                perror("Can't read from eventfd");
                return -1;
            }
            if ((num == terminate_num) || (read_bytes == 0)) {
                break;
            }
            printf("%lu\n", num);
        }
    }
    return 0;
}