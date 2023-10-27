// solution by Alexey Zertsalov

#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct {
    pthread_t thread;
    _Atomic volatile int* counter;
} thread_data;

static void* thread_func(void* arg) {
    thread_data* data_ptr = (thread_data*)arg;
    for (int i = 0; i < 10000000; i++) {
        atomic_fetch_add(data_ptr->counter, 1);
    }
    return NULL;
}

int main() {
    const int THREADS_COUNT = 10;
    thread_data threads[THREADS_COUNT];
    _Atomic volatile int shared_counter = 0;
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
