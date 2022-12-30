#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include "definitions.h"
#include "test.h"

static void test(void *lock, void testFunc(int, void *f(void*), void*), void *unitFunc(void*)) {
    ThreadContext *context = malloc(sizeof(ThreadContext));
    context->data = lock;
    context->counter = 0;

    const int count = 4;
    testFunc(count, unitFunc, (void *)context);

    const int counter = context->counter;
    free(context);

    assert_int_equal(counter, THREAD_LOOPS * count);
}


static void thread_runPool(const int count, void *func(void*), void *data) {
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

static void process_runPool(int count, void *func(void*), void *data) {
    for (int i = 0; i < count; i++) {
        int pid = fork();
        if (-1 == pid) {
            error("can not create process");
        }

        func(data);

        if (0 == pid) {
            exit(EXIT_SUCCESS);
        }
    }

    wait(NULL);
}


void threads_test(void *lock, void *func(void*)) {
    test(lock, thread_runPool, func);
}

void process_test(void *lock, void *func(void*)) {
    test(lock, process_runPool, func);
}
