#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    size_t* arr;
    size_t l;
    size_t r;
} task_args;

typedef struct {
    size_t sum;
} task_res;

task_res* thread_sum(task_args *arg) {
    task_res* res = malloc(sizeof(task_res));
    res->sum = 0;
    for (size_t i = arg->l; i < arg->r; i++) {
        res->sum += arg->arr[i];
        for (size_t j = 0; j < 10; j++) {
            res->sum += j;
        }
    }
    return res;
} 

int main(int argc, char **argv) {
    const size_t MAXN = 100000000;
    size_t* arr = malloc(sizeof(size_t) * MAXN);
    for (int i = 0; i < MAXN; i++) {
        arr[i] = i * i;
    }

    clock_t begin = clock();

    const size_t THREAD_COUNT = atoi(argv[1]);
    pthread_t threads[THREAD_COUNT];
    for (size_t i = 0; i < THREAD_COUNT; ++i) {
        task_args thread_args;
        thread_args.l = (MAXN * i) / THREAD_COUNT;
        thread_args.r = (MAXN * (i + 1)) / THREAD_COUNT;
        thread_args.arr = arr;
        pthread_create(&threads[i], NULL, thread_sum, &thread_args);
    }

    size_t sum = 0;
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        task_res* res;
        pthread_join(threads[i], &res);
        sum += res->sum;
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Calculated sum %lu in %lf\n", sum, time_spent);
    return 0;
}
