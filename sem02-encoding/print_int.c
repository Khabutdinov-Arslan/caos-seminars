#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

void printBits(size_t size, void* ptr)
{
    unsigned char *bytes = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (bytes[i] >> j) & 1;
            printf("%u", byte);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    uint8_t up = 27;
    printf("uint8_t  27: ");
    printBits(sizeof(up), &up);
    int8_t sp = 27;
    printf("int8_t   27: ");
    printBits(sizeof(sp), &sp);
    int8_t sn = -27;
    printf("int8_t  -27: ");
    printBits(sizeof(sn), &sn);
    uint16_t lp = 27;
    printf("uint16_t 27 (little endian): ");
    printBits(sizeof(lp), &lp);
    uint16_t no = htons(27);
    printf("uint16_t 27    (big endian): ");
    printBits(sizeof(no), &no);
    return 0;
}