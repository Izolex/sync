#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>
#include "../include/semaphore_spin.h"
#include "definitions.h"

const atomic_flag atomicFlagInitializer = ATOMIC_FLAG_INIT;

typedef struct semaphoreSpin {
    atomic_int value;
    atomic_flag mutex;
} SemaphoreSpin;


SemaphoreSpin *semaphoreSpin_create(const int maximum) {
    SemaphoreSpin *sem = malloc(sizeof(SemaphoreSpin));
    if (NULL == sem) {
        error("can not allocate memory for semaphore spin");
    }

    sem->value = maximum;

    memcpy(&sem->mutex, &atomicFlagInitializer, sizeof(atomicFlagInitializer));

    return sem;
}

void semaphoreSpin_free(SemaphoreSpin *sem) {
    free(sem);
}

void semaphoreSpin_wait(SemaphoreSpin *sem) {
    while (atomic_flag_test_and_set_explicit(&sem->mutex, memory_order_acquire)) {
        cpu_relax();
    }

    while (0 >= atomic_load_explicit(&sem->value, memory_order_acquire)) {
        atomic_fetch_sub_explicit(&sem->value, 1, memory_order_release);
    }

    atomic_flag_clear_explicit(&sem->mutex, memory_order_release);
}

void semaphoreSpin_signal(SemaphoreSpin *sem) {
    atomic_fetch_add_explicit(&sem->value, 1, memory_order_release);
}
