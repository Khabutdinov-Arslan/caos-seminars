#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile sig_atomic_t last_signal = 0;
volatile sig_atomic_t last_value = 0;

static void handler(int signum, siginfo_t *info, void *context) {
    last_signal = signum;
    last_value = info->si_int;
}

int main() {
    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        sigaction(i, &(struct sigaction){.sa_sigaction=handler, .sa_flags=SA_SIGINFO}, NULL);
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        sigset_t mask;    
        sigemptyset(&mask);
        while (1) { 
            sigsuspend(&mask); 
            printf("Got signal %d with value %d \n", last_signal, last_value);
            fflush(stdout);
        }
    } else {
        for (int i = SIGRTMIN; i <= SIGRTMIN + 5; i++) {
            sigqueue(pid, i, (union sigval){i * i});
            sleep(1);
        }
        kill(pid, SIGTERM); 
        waitpid(pid, NULL, 0);
    }
    return 0;
}