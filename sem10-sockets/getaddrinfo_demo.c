#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
    struct addrinfo* res = NULL;
    getaddrinfo(argv[1], "80", 0, &res);

    struct addrinfo* i;

    for(i=res; i!=NULL; i=i->ai_next)
    {
        char str[INET6_ADDRSTRLEN];
        if (i->ai_addr->sa_family == AF_INET) {
            struct sockaddr_in *p = (struct sockaddr_in *)i->ai_addr;
            printf("%s\n", inet_ntop(AF_INET, &p->sin_addr, str, sizeof(str)));
        }
    }

    freeaddrinfo(res);

    return 0;
}
