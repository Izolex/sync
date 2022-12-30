#include "../include/mutex.h"
#include "definitions.h"
#include "mutex.h"
#include "test.h"


static void *threadFunc_private(void *data) {
    ThreadContext *context = (ThreadContext*)data;

    mutex_lockPrivate((MutexPrivate*)context->data);
    for (int i = 0; i < THREAD_LOOPS; i++) {
        context->counter++;
    }
    mutex_unlockPrivate((MutexPrivate*)context->data);

    return NULL;
}

static void *threadFunc_shared(void *data) {
    ThreadContext *context = (ThreadContext*)data;

    mutex_lockShared((MutexShared*)context->data);
    for (int i = 0; i < THREAD_LOOPS; i++) {
        context->counter++;
    }
    mutex_unlockShared((MutexShared*)context->data);

    return NULL;
}


void test_mutexPrivate(unused void **state) {
    MutexPrivate mutex = mutex_createPrivate();
    threads_test(&mutex, threadFunc_private);
}

void test_mutexShared(unused void **state) {
    MutexShared *sharedMemory = mutex_createShared();
    process_test(&sharedMemory[0], threadFunc_shared);
    mutex_sharedFree(sharedMemory);
}
