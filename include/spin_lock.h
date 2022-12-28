#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

#include <stdatomic.h>
#include <stdbool.h>

typedef atomic_flag SpinLockTAS;
SpinLockTAS spinLockTAS_create(void);
void spinLockTAS_lock(SpinLockTAS *sl);
void spinLockTAS_unlock(SpinLockTAS *sl);

typedef _Atomic bool SpinLockTTAS;
SpinLockTTAS spinLockTTAS_create(void);
void spinLockTTAS_lock(SpinLockTTAS *sl);
void spinLockTTAS_unlock(SpinLockTTAS *sl);

#endif
