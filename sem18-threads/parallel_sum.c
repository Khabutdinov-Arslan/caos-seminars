#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    size_t l;
    size_t r;
} task_args;

typedef struct {
    size_t sum;
} task_res;

void* thread_sum(void *p_arg) {
    task_args* arg = (task_args*)p_arg;
    task_res* res = malloc(sizeof(task_res));
    res->sum = 0;
    for (size_t i = arg->l; i < arg->r; i++) {
        res->sum += i;
    }
    return res;
}

int main(int argc, char **argv) {
    const size_t MAXN = 1000000000;
    const size_t THREAD_COUNT = atoi(argv[1]);
    pthread_t threads[THREAD_COUNT];
    task_args thread_args[THREAD_COUNT];
    for (size_t i = 0; i < THREAD_COUNT; ++i) {
        thread_args[i].l = (MAXN * i) / THREAD_COUNT;
        thread_args[i].r = (MAXN * (i + 1)) / THREAD_COUNT;
        pthread_create(&threads[i], NULL, thread_sum, &thread_args[i]);
    }

    size_t sum = 0;
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        void* res_p;
        pthread_join(threads[i], &res_p);
        task_res* res = (task_res*)res_p;
        sum = (sum + res->sum);
        free(res);
    }

    printf("Calculated sum %lu\n", sum);
    return 0;
}
