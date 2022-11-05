#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int BUFF_SIZE = 4096;

int server_socket_init(uint16_t port)
{
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct in_addr input_address;
    input_address.s_addr = inet_addr("127.0.0.1");
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr = input_address;
    server_address.sin_port = htons(port);

    int connection_status = bind(
        server_fd, (struct sockaddr*)&server_address, sizeof(server_address));
    if (connection_status) {
        perror("Bind failed: ");
        exit(1);
    }

    int listening_status = listen(server_fd, SOMAXCONN);
    if (listening_status) {
        perror("Listen failed: ");
        exit(1);
    }
    return server_fd;
}

void read_message(int client_fd, char* buff){
    read(client_fd, buff, BUFF_SIZE);
}

void write_message(int client_fd, char* buff){
    write(client_fd, buff, strlen(buff));
}

int main(int argc, char* argv[])
{
    int server_fd = server_socket_init(atoi(argv[1]));
    while (true) {
        int client_fd = accept(server_fd, NULL, NULL);
        char msg[BUFF_SIZE];
        while (1) {
            read_message(client_fd, msg);
            if (msg[0] == 'q') {
                break;
            }
            write_message(client_fd, msg);
        }
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    }
    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
    return 0;
}
