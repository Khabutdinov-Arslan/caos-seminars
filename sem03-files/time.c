#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>

int main() {
    struct timespec spec = {0}; 
    clock_gettime(CLOCK_REALTIME, &spec);
    struct tm local_tm = {0};
    localtime_r(&spec.tv_sec, &local_tm);
    char time_str[100]; 
    size_t time_len = strftime(time_str, sizeof(time_str), "%Y.%m.%d %H:%M:%S", &local_tm);
    printf("%s\n", time_str);
}