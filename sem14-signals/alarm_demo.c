#include <unistd.h>
#include <stdio.h>

int main() {
    alarm(3);
    pause();
    return 1;
}