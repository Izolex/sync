#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "definitions.h"
#include "spin_lock.h"

int main(unused int argc, unused char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_spinLockTAS),
            cmocka_unit_test(test_spinLockTTAS),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
