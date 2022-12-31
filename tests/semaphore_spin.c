#include "definitions.h"
#include "../include/semaphore_spin.h"
#include "semaphore_spin.h"
#include "test.h"

static void *threadFunc_semaphoreSpin(void *data) {
    ThreadContext *context = (ThreadContext*)data;

    semaphoreSpin_wait((struct semaphoreSpin*)context->data);
    for (int i = 0; i < THREAD_LOOPS; i++) {
        context->counter++;
    }
    semaphoreSpin_signal((struct semaphoreSpin*)context->data);

    return NULL;
}


void test_semaphoreSpin(unused void **state) {
    struct semaphoreSpin *sem = semaphoreSpin_create(1);
    threads_test(sem, threadFunc_semaphoreSpin);
    semaphoreSpin_free(sem);
}
