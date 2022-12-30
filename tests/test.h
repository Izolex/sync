#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include "definitions.h"

#define THREAD_LOOPS 10000000

typedef struct {
    void *data;
    int counter;
} ThreadContext;

void threads_test(void *lock, void *func(void*));
void process_test(void *lock, void *func(void*));


#endif
