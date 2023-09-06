#include <fcntl.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <unistd.h>
#include <values.h>

int main()
{
    const int HASH_SIZE = 512 / CHAR_BIT;
    SHA512_CTX context;
    SHA512_Init(&context);

    char buff[HASH_SIZE];
    while (1) {
        size_t read_during_iteration = read(0, buff, sizeof(buff));
        if (read_during_iteration == 0){
            break;
        }else{
            SHA512_Update(&context, buff, read_during_iteration);
        }
    }

    unsigned char hash[HASH_SIZE];
    SHA512_Final(hash, &context);
    printf("0x");
    for (size_t i = 0; i < sizeof(hash); i++){
        printf("%02"PRIx32, hash[i]&0xffU);
    }
    printf("\n");

    return 0;
}