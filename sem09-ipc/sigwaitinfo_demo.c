#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    sigprocmask(SIG_BLOCK, &mask, NULL);

    siginfo_t info;

    while (1) {
        int signum = sigwaitinfo(&mask, &info);
        printf("%s siginfo=%d, signum=%d\n", "Received signal", info.si_signo, signum);
        fflush(stdout);
    }
    
    return 0;
}
