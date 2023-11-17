#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <signal.h>

struct my_ping {
    struct icmphdr hdr;
    char buffer[64 - sizeof(struct icmphdr)];
};

unsigned short in_cksum(unsigned short *ptr, int nbytes) {
    register long sum;
    u_short oddbyte;
    register u_short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char *) & oddbyte) = *(u_char *) ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;

    return (answer);
}

int wake = 0;

void handler(int i) {
    wake = 1;
}


// args: server addr, total timeout, sleep between attempts
int main(int argc, char* argv[]) {
    int interval = atoi(argv[3]);

    int client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    
    signal(SIGALRM, handler);
    alarm(atoi(argv[2]));


    int out = 0;

    while(!wake) {
        struct my_ping paket = {
                .hdr.type = 8,
                .hdr.code = 0,
                .hdr.un.echo.id = getpid(),
                .hdr.un.echo.sequence = out,
        };

        paket.hdr.checksum = in_cksum((unsigned short*)&paket, sizeof(paket));

        sendto(client_fd, (const char *)&paket, sizeof(paket),
            0, (const struct sockaddr *) &server_addr, 
            sizeof(server_addr));
        socklen_t len;
        size_t length = recvfrom(client_fd, (char *)&paket, sizeof(paket), 
                    0, (struct sockaddr *) &server_addr, &len);
        ++ out;
        usleep(interval);
    }
    close(client_fd); 
    printf("%i\n", out);
}