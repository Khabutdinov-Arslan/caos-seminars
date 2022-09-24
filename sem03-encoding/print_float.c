#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

void printBits(size_t size, void* ptr)
{
    unsigned char *bytes = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = 3; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (bytes[i] >> j) & 1; // get j-th bit
            printf("%u", byte);
            if ((i >= 2) && (j == 7)) {
                printf(" ");
            }
        }
    }
    printf("\n");
}

int main() {
    float op = 1.0;
    printf(" 1.0: ");
    printBits(sizeof(op), &op);
    float on = -1.0;
    printf("-1.0: ");
    printBits(sizeof(on), &on);
    float ep = 8.0;
    printf(" 8.0: ");
    printBits(sizeof(on), &ep);
    float hp = 0.5;
    printf(" 0.5: ");
    printBits(sizeof(hp), &hp);
    float hl = 2.5;
    printf(" 2.5: ");
    printBits(sizeof(hp), &hl);
    float hm = 149.0;
    printf("149.0: ");
    printBits(sizeof(hm), &hm);
    return 0;
}