#include <stdbool.h>
#include <stdatomic.h>
#include "definitions.h"
#include "spin_lock.h"

/**
 * TAS
 */
SpinLockTAS spinLockTAS_create(void) {
    SpinLockTAS sl = ATOMIC_FLAG_INIT;
    return sl;
}

void spinLockTAS_lock(SpinLockTAS *sl) {
    while (atomic_flag_test_and_set_explicit(sl, memory_order_acquire));
}

void spinLockTAS_unlock(SpinLockTAS *sl) {
    atomic_flag_clear_explicit(sl, memory_order_release);
}


/**
 * TTAS
 */
SpinLockTTAS spinLockTTAS_create(void) {
    return ATOMIC_VAR_INIT(false);
}

void spinLockTTAS_lock(SpinLockTTAS *sl) {
    for (;;) {
        if (!atomic_exchange_explicit(sl, true, memory_order_acquire)) {
            break;
        }
        while (atomic_load_explicit(sl, memory_order_relaxed)) {
            cpu_relax();
        }
    }
}

void spinLockTTAS_unlock(SpinLockTTAS *sl) {
    atomic_store_explicit(sl, false, memory_order_release);
}
