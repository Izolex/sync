#include "definitions.h"
#include "../include/semaphore.h"
#include "semaphore.h"
#include "test.h"

static void *threadFunc_semaphore(void *data) {
    ThreadContext *context = (ThreadContext*)data;

    semaphore_wait((struct semaphore*)context->data);
    for (int i = 0; i < THREAD_LOOPS; i++) {
        context->counter++;
    }
    semaphore_signal((struct semaphore*)context->data);

    return NULL;
}


void test_semaphore(unused void **state) {
    struct semaphore *sem = semaphore_create(1);
    threads_test(sem, threadFunc_semaphore);
    semaphore_free(sem);
}
