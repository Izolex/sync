#include <pthread.h>
#include <string.h>
#include "definitions.h"
#include "semaphore.h"

const pthread_cond_t initializerCondition = PTHREAD_COND_INITIALIZER;
const pthread_mutex_t initializerMutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct semaphore {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    int ready, value;
} Semaphore;


static void safeMutexLock(pthread_mutex_t *mutex) {
    if (unlikely(0 != pthread_mutex_lock(mutex))) {
        error("can not lock mutex");
    }
}

static void safeMutexUnlock(pthread_mutex_t *mutex) {
    if (unlikely(0 != pthread_mutex_unlock(mutex))) {
        error("can not unlock mutex");
    }
}


Semaphore *semaphore_create(const int maximum) {
    Semaphore *sem = malloc(sizeof(Semaphore));
    if (NULL == sem) {
        error("can not allocate memory for semaphore");
    }
    sem->ready = maximum;
    sem->value = maximum;

    memcpy(&sem->mutex, &initializerMutex, sizeof(initializerMutex));
    memcpy(&sem->cond, &initializerCondition, sizeof(initializerCondition));

    return sem;
}

void semaphore_free(Semaphore *sem) {
    free(sem);
}

void semaphore_wait(Semaphore *sem) {
    safeMutexLock(&sem->mutex);
    sem->value--;

    if (sem->value < 0) {
        do {
            if (unlikely(0 != pthread_cond_wait(&sem->cond, &sem->mutex))) {
                error("can not wait cond");
            }
        } while (sem->ready < 1);
        sem->ready--;
    }

    safeMutexUnlock(&sem->mutex);
}


void semaphore_signal(Semaphore *sem) {
    safeMutexLock(&sem->mutex);
    sem->value++;

    if (sem->value <= 0) {
        sem->ready++;
        if (unlikely(0 != pthread_cond_signal(&sem->cond))) {
            error("can not signal cond");
        }
    }

    safeMutexUnlock(&sem->mutex);
}
