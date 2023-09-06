#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t current_num;
    int32_t num_updated;
    pthread_mutex_t* syncer;
    pthread_cond_t* prime_ready;

} thread_data;

void* worker(void* arg)
{

    thread_data* data_ptr = (thread_data*)arg;
    for (int64_t i = 0; i < 10; i++) {
        pthread_mutex_lock(data_ptr->syncer);
        while (data_ptr->num_updated == 1) {
            pthread_cond_wait(data_ptr->prime_ready, data_ptr->syncer);
        }
        data_ptr->current_num = i * i;
        data_ptr->num_updated = 1;
        pthread_cond_signal(data_ptr->prime_ready);
        pthread_mutex_unlock(data_ptr->syncer);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_mutex_t syncer;
    pthread_mutex_init(&syncer, NULL);
    pthread_cond_t prime_ready;
    pthread_cond_init(&prime_ready, NULL);
    thread_data data;
    data.syncer = &syncer;
    data.prime_ready = &prime_ready;
    data.num_updated = 0;
    data.current_num = 0;

    pthread_t finder;

    pthread_create(&finder, NULL, worker, (void*)&data);
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&syncer);
        while (data.num_updated == 0) {
            pthread_cond_wait(&prime_ready, &syncer);
        }
        printf("%ld ", data.current_num);
        fflush(stdout);
        pthread_cond_signal(data.prime_ready);
        data.num_updated = 0;
        pthread_mutex_unlock(&syncer);
    }
    printf("\n");

    pthread_join(finder, NULL);

    return 0;
}
