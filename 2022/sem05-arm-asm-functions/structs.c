#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>

typedef struct usual_struct
{
    char name[14];
    uint64_t balance;
    uint8_t age;
} usual_struct;

typedef struct reordered_struct
{
    uint64_t balance;
    char name[14];
    uint8_t age;
} reordered_struct;


typedef struct __attribute__((__packed__))  packed_struct
{
    char name[14];
    uint64_t balance;
    uint8_t age;
} packed_struct;

typedef struct outer  {
    usual_struct man;
    uint64_t counter;
} outer;


int main() {
    usual_struct usual_man;
    printf("usual_struct size  = %u\n", sizeof(usual_man));
    printf("usual_struct align = %u\n", alignof(usual_man));
    printf("name    address = %p\n", &usual_man.name);
    printf("balance address = %p\n", &usual_man.balance);
    printf("age     address = %p\n", &usual_man.age);
    reordered_struct reordered_man;
    printf("reordered_struct size  = %u\n", sizeof(reordered_man));
    printf("reordered_struct align = %u\n", alignof(reordered_man));
    printf("name    address = %p\n", &reordered_man.name);
    printf("balance address = %p\n", &reordered_man.balance);
    printf("age     address = %p\n", &reordered_man.age);
    packed_struct packed_man;
    printf("packed_struct size  = %u\n", sizeof(packed_man));
    printf("packed_struct align = %u\n", alignof(packed_man));
    printf("name    address = %p\n", &packed_man.name);
    printf("balance address = %p\n", &packed_man.balance);
    printf("age     address = %p\n", &packed_man.age);
    return 0;
}