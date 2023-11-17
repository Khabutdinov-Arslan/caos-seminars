#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 4096

typedef struct {
    int fd;
    char buffer[BUFF_SIZE];
    int buffer_begin;
    int buffer_end;
} fd_data;

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
        perror("Connection failed: ");
        exit(1);
    }

    int listening_status = listen(server_fd, SOMAXCONN);
    if (listening_status) {
        perror("Listen failed: ");
        exit(1);
    }
    return server_fd;
}

void disable_io_block(int fd)
{
    int current_descriptor_flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, current_descriptor_flags | O_NONBLOCK);
}

void read_buff(fd_data* data) {
    data->buffer_end = read(data->fd, data->buffer, BUFF_SIZE);
}

void write_buff(fd_data* data) {
    data->buffer_begin += write(data->fd, data->buffer + data->buffer_begin, data->buffer_end - data->buffer_begin);
    if (data->buffer_begin == data->buffer_end) {
        data->buffer_begin = data->buffer_end = 0;
    }
}

void process_epoll_event(struct epoll_event* event, int server_fd, int epoll_fd)
{
    if (event->data.fd == server_fd) {
        int client_fd = accept(server_fd, NULL, NULL);
        disable_io_block(client_fd);

        struct epoll_event client_event;
        fd_data* add_data = calloc(1, sizeof(*add_data));
        add_data->fd = client_fd;
        add_data->buffer_begin = 0;
        add_data->buffer_end = 0;
        client_event.data.ptr = add_data;
        client_event.events = EPOLLIN | EPOLLOUT | EPOLLHUP;

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) < 0) {
            perror("Add client to epoll failed: ");
        }

    } else {
        const uint32_t mask = event->events;
        fd_data* data = event->data.ptr;
        if ((mask & EPOLLIN) && (data->buffer_end == 0)) {
            read_buff(data);
        }
        if ((mask & EPOLLOUT) && (data->buffer_end != 0)) {
            write_buff(data);
        }
        if (mask & EPOLLHUP) {
            free(data);
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event->data.fd, NULL);
        }
    }
}

int main(int argc, char* argv[])
{
    int server_fd = server_socket_init(atoi(argv[1]));
    
    disable_io_block(server_fd);

    struct epoll_event listen_event;
    int epoll_fd = epoll_create1(0);

    listen_event.events = EPOLLIN;
    listen_event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &listen_event) < 0) {
        perror("Adding server socket to epoll failed: ");
        exit(1);
    }

    const int MAX_PENDING_EVENTS_COUNT = 64000;
    struct epoll_event pending_events[MAX_PENDING_EVENTS_COUNT];

    while (1) {
        int pending_events_count =
            epoll_wait(epoll_fd, pending_events, MAX_PENDING_EVENTS_COUNT, -1);
        for (size_t i = 0; i < pending_events_count; i++) {
            process_epoll_event(&pending_events[i], server_fd, epoll_fd);
        }
    }

    close(epoll_fd);
    close(server_fd);
    return 0;
}
