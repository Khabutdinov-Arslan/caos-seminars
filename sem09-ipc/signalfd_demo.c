#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGCONT);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int fd = signalfd(-1, &mask, 0);
    struct signalfd_siginfo fdsi;
    while (true) {
        read(fd, &fdsi, sizeof(struct signalfd_siginfo));
        printf("Got signal %d\n", fdsi.ssi_signo);
    }
    close(fd);
    return 0;
}
