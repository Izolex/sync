#ifndef FUTEX_H
#define FUTEX_H

typedef int MutexPrivate;
MutexPrivate mutex_createPrivate(void);
void mutex_lockPrivate(MutexPrivate *mut);
void mutex_unlockPrivate(MutexPrivate *mut);

typedef int MutexShared;
MutexShared *mutex_createShared(void);
void mutex_sharedFree(void *sharedMemory);
void mutex_lockShared(MutexShared *mut);
void mutex_unlockShared(MutexShared *mut);

#endif
