#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timerfd.h>

int main() {
    int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    struct itimerspec itval;
    itval.it_interval.tv_sec = 1;
	itval.it_interval.tv_nsec = 0;
	itval.it_value.tv_sec = 1;
	itval.it_value.tv_nsec = 0;
    int st = timerfd_settime(fd, 0, &itval, NULL);

    unsigned long long missed;
    while (1) {
        int ret = read(fd, &missed, sizeof(missed));
        printf("%s %llu\n", "Interval signal ", missed);
        fflush(stdout);
    }

    return 0;
}
