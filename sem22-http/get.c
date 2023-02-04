#include <netdb.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    signal(SIGPIPE, SIG_IGN);
    char* hostname = argv[1];
    char* path = argv[2];

    struct addrinfo addr_hints = {.ai_family = AF_INET,
                                  .ai_socktype = SOCK_STREAM};
    struct addrinfo* addr_res = NULL;
    getaddrinfo(hostname, "http", &addr_hints, &addr_res);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(sock_fd, addr_res->ai_addr, addr_res->ai_addrlen)) {
        perror("Couldn't connect to server");
        exit(1);
    }

    const int BUFF_SIZE = 1000000;
    char buff[BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    snprintf(
        buff,
        sizeof(buff),
        "GET %s HTTP/1.1\nHost: %s\nConnection: close\n\n",
        path,
        hostname);
    if (send(sock_fd, buff, strlen(buff), 0) == -1) {
        perror("Couldn't send request");
        exit(1);
    }
    memset(buff, 0, BUFF_SIZE);

    FILE *sock_f = fdopen(sock_fd, "r");
    bool headers_found = 0;
    while (fgets(buff, sizeof(buff), sock_f)){
        if ((strcmp(buff, "\n") == 0) || (strcmp(buff, "\r\n")) == 0){
            headers_found = 1;
            continue;
        }
        if (headers_found){
            printf("%s", buff);
        }
    }

    fclose(sock_f);
    return 0;
}
