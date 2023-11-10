#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct in_addr input_address;
    input_address.s_addr = inet_addr(argv[1]);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr = input_address;
    server_address.sin_port = htons(atoi(argv[2]));

    int connection_status = bind(fd, (struct sockaddr*)&server_address, sizeof(server_address));
    if (connection_status) {
        perror("Bind failed: ");
        exit(1);
    }

    const int BUFF_SIZE = 4096;
    char buff[BUFF_SIZE];
    while (1) {
        struct in_addr client_address;
        socklen_t client_address_length;
        if (recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr*)&client_address,
            &client_address_length) == 0) {
            break;
        }
        sendto(fd, buff, strlen(buff), 0, (const struct sockaddr*)&client_address,
            client_address_length);
        fflush(stdout);
        printf("%s\n", buff);
    }

    close(fd);
    return 0;
}
