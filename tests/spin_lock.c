#include "../include/spin_lock.h"
#include "definitions.h"
#include "spin_lock.h"
#include "test.h"


static void *threadFunc_TAS(void *data) {
    ThreadContext *context = (ThreadContext*)data;

    spinLockTAS_lock((SpinLockTAS*)context->data);
    for (int i = 0; i < THREAD_LOOPS; i++) {
        context->counter++;
    }
    spinLockTAS_unlock((SpinLockTAS*)context->data);

    return NULL;
}

static void *threadFunc_TTAS(void *data) {
    ThreadContext *context = (ThreadContext*)data;

    spinLockTTAS_lock((SpinLockTTAS*)context->data);
    for (int i = 0; i < THREAD_LOOPS; i++) {
        context->counter++;
    }
    spinLockTTAS_unlock((SpinLockTTAS*)context->data);

    return NULL;
}


void test_spinLockTAS(unused void **state) {
    SpinLockTAS lock = spinLockTAS_create();
    threads_test(&lock, threadFunc_TAS);
}

void test_spinLockTTAS(unused void **state) {
    SpinLockTTAS lock = spinLockTTAS_create();
    threads_test(&lock, threadFunc_TTAS);
}
