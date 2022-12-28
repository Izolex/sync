#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include <pthread.h>
#include "definitions.h"

#define THREAD_LOOPS 77000000

typedef struct {
    void *data;
    int counter;
} ThreadContext;

static void threads_runPool(const int count, void *func(void*), void *data) {
    pthread_t threads[count];

    for (int i = 0; i < count; i++) {
        if (0 != pthread_create(&threads[i], NULL, func, data)) {
            error("can not create thread");
        }
    }
    for (int i = 0; i < count; i++) {
        if (0 != pthread_join(threads[i], NULL)) {
            error("can not join thread");
        }
    }
}

static void threads_test(void *lock, void *threadFunc(void*)) {
    ThreadContext *context = malloc(sizeof(ThreadContext));
    context->data = lock;
    context->counter = 0;

    const int threadCount = 4;
    threads_runPool(threadCount, threadFunc, (void *)context);

    const int counter = context->counter;
    free(context);

    assert_int_equal(counter, THREAD_LOOPS * threadCount);
}

#endif
