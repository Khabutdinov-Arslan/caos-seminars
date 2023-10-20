#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct {
    pthread_t thread;
    int* counter;
    pthread_mutex_t* syncer;
} thread_data;

static void* thread_func(void* arg) {
    thread_data* data_ptr = (thread_data*)arg;
    int local_counter = 0;
    for (int i = 0; i < 100000000; i++) {
        local_counter++;
    }
    pthread_mutex_lock(data_ptr->syncer);
    (*(data_ptr->counter)) += local_counter;
    pthread_mutex_unlock(data_ptr->syncer);
    return NULL;
}

int main() {
    pthread_mutex_t syncer;
    pthread_mutex_init(&syncer, NULL);

    const int THREADS_COUNT = 10;
    thread_data threads[THREADS_COUNT];
    int shared_counter = 0;
    for (int i = 0; i < THREADS_COUNT; i++) {
        threads[i].counter = &shared_counter;
        threads[i].syncer = &syncer;
        pthread_create(&threads[i].thread, NULL, thread_func,  (void*)&threads[i]);
    }
    for (int i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i].thread, NULL);
    }
    printf("%d\n", shared_counter);
    return 0;
}