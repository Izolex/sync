#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct semaphore;

struct semaphore *semaphore_create(int maximum);
void semaphore_free(struct semaphore *sem);
void semaphore_wait(struct semaphore *sem);
void semaphore_signal(struct semaphore *sem);

#endif
