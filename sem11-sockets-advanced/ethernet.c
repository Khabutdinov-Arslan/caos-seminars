#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <linux/if_ether.h>

int main() {
    int sock_fd = socket(AF_PACKET,SOCK_RAW, htons(ETH_P_ALL));
    if (sock_fd < 0) {
        perror("Couldn't open socket: ");
        return -1;
    }
    const int BUFF_SIZE = 65536;
    char buff[BUFF_SIZE];
    struct sockaddr saddr;
    int saddr_len = sizeof (saddr); 
    memset(buff, 0, BUFF_SIZE);
    int packet_length = recvfrom(sock_fd,buff,BUFF_SIZE,0,&saddr,(socklen_t *)&saddr_len);
    if (packet_length < 0) {
        perror("Couldn't read from socket");
        return -1;
    }
    struct ethhdr *eth = (struct ethhdr *)(buff);
    printf("Source Address: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
    printf("Destination Address: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
    printf("Protocol: %d\n",eth->h_proto);
    return 0;
}