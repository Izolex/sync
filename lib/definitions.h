#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#define cpu_relax() __asm__ __volatile__("pause\n" : : : "memory")
#define cpu_relax() __asm__ __volatile__("yield");

#define futex(uaddr, futex_op, val)\
    syscall(SYS_futex, (uaddr), (futex_op), (val), NULL, NULL, 0)

#define error(msg) do { perror((msg)); exit(EXIT_FAILURE); } while (0)

#ifdef __GNUC__
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x) (x)
#define unlikely(x) (x)
#endif

#endif
