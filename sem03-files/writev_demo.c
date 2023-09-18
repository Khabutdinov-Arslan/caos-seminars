#include <sys/uio.h>

#include <unistd.h>
#include <string.h>

int main()
{   
    char buff1[] = "buff1 ", buff2[] = "buff2\n";
    struct iovec buffs[] = {
        {buff1, strlen(buff1)},
        {buff2, strlen(buff2)},
    };
    writev(1, buffs, 2);
    return 0;
}
