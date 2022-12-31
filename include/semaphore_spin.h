#ifndef SEMAPHORE_SPIN_H
#define SEMAPHORE_SPIN_H

struct semaphoreSpin *semaphoreSpin_create(int maximum);
void semaphoreSpin_free(struct semaphoreSpin *sem);
void semaphoreSpin_wait(struct semaphoreSpin *sem);
void semaphoreSpin_signal(struct semaphoreSpin *sem);

#endif
