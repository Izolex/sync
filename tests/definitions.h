#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define unused __attribute__((unused))
#define cpu_relax() __asm__ __volatile__("yield");
#define error(msg) do { perror((msg)); exit(EXIT_FAILURE); } while (0)

#endif
