#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t received_sigint = 0;

void sigint_handler(int signum)
{
    received_sigint = 1;
}

void set_handler(int signum, void* handler, struct sigaction* action)
{
    action->sa_handler = handler;
    action->sa_flags = SA_RESTART;
    sigaction(signum, action, NULL);
}

int main() {
    struct sigaction sigint_action;
    memset(&sigint_action, 0, sizeof(sigint_action));
    set_handler(SIGINT, sigint_handler, &sigint_action);

    printf("%d\n", getpid());
    fflush(stdout);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    while (1) {
        sigprocmask(SIG_BLOCK, &mask, NULL);
        sleep(5);
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
        if (received_sigint) {
            printf("%s\n", "SIGINT received");
            fflush(stdout);
            received_sigint = 0;
        }
    }
    return 0;
}
