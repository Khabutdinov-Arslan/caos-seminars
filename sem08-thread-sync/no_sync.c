// solution by Alexey Zertsalov

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct {
    pthread_t thread;
    int* counter;
} thread_data;

static void* thread_func(void* arg) {
    thread_data* data_ptr = (thread_data*)arg;
    for (int i = 0; i < 30000; i++) {
        ++(*(data_ptr->counter));
    }
    return NULL;
}

int main() {
    const int THREADS_COUNT = 10;
    thread_data threads[THREADS_COUNT];
    int shared_counter = 0;
    for (int i = 0; i < THREADS_COUNT; i++) {
        threads[i].counter = &shared_counter;
        pthread_create(&threads[i].thread, NULL, thread_func,  (void*)&threads[i]);
    }
    for (int i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i].thread, NULL);
    }
    printf("%d\n", shared_counter);
    return 0;
}
