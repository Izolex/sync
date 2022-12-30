#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <linux/futex.h>
#include "definitions.h"
#include "mutex.h"

enum {
    unlocked = 0,
    locked_no_waiters = 1,
    locked_waiters = 2,
};


static int compare_exchange(int *mut, int expected, const int desired) {
    int *value = &expected;
    atomic_compare_exchange_strong_explicit((_Atomic int *)mut, value, desired, memory_order_acquire, memory_order_acquire);
    return *value;
}

static void mutex_unlock(int *mut, int futex_op) {
    if (atomic_fetch_sub_explicit((_Atomic int *)mut, 1, memory_order_acquire) != locked_no_waiters) {
        atomic_store_explicit((_Atomic int *)mut, unlocked, memory_order_release);

        long r = futex((u_int32_t *)mut, futex_op, locked_no_waiters);
        if (unlikely(-1 == r)) {
            error("futex error");
        }
    }
}

static void mutex_lock(int *mut, int futex_op) {
    int c = compare_exchange(mut, unlocked, locked_no_waiters);
    if (unlocked != c) {
        do {
            if (locked_waiters == c || unlocked != compare_exchange(mut, locked_no_waiters, locked_waiters)) {
                long r = futex((u_int32_t *)mut, futex_op, locked_waiters);
                if (unlikely(-1 == r) && errno != EAGAIN) {
                    error("futex error");
                }
            }

            cpu_relax();
        } while (unlocked != (c == compare_exchange(mut, unlocked, locked_waiters)));
    }
}


MutexPrivate mutex_createPrivate(void) {
    return ATOMIC_VAR_INIT(0);
}

void mutex_lockPrivate(MutexPrivate *mut) {
    mutex_lock(mut, FUTEX_WAIT_PRIVATE);
}

void mutex_unlockPrivate(MutexPrivate *mut) {
    mutex_unlock(mut, FUTEX_WAKE_PRIVATE);
}


MutexShared *mutex_createShared(void) {
    MutexShared *sharedMemory = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (unlikely(MAP_FAILED == sharedMemory)) {
        error("can not create shared memory");
    }

    return sharedMemory;
}

void mutex_sharedFree(void *sharedMemory) {
    munmap(sharedMemory, sizeof(int));
}

void mutex_lockShared(MutexShared *mut) {
    mutex_lock(mut, FUTEX_WAIT);
}

void mutex_unlockShared(MutexShared *mut) {
    mutex_unlock(mut, FUTEX_WAKE);
}
