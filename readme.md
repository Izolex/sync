Synchronization
-

Implementation of a few [synchronization primitives](https://en.wikipedia.org/wiki/Synchronization_(computer_science)) using [atomics](https://en.wikipedia.org/wiki/Linearizability) (with explicit [memory order](https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync)) and other techniques.
Project uses [CMake](https://cmake.org/) and [cmocka](https://cmocka.org/).
Simple tests can be run by `$ docker-compose up --build` command.

- [Lock](https://en.wikipedia.org/wiki/Lock_(computer_science)) ([mutex](https://en.wikipedia.org/wiki/Mutual_exclusion)) using [Futex](https://en.wikipedia.org/wiki/Futex) with [CAS](https://en.wikipedia.org/wiki/Compare-and-swap) (supports [private Futex](https://lwn.net/Articles/229668/)) 
- [Spinlock](https://en.wikipedia.org/wiki/Spinlock) using [TAS](https://en.wikipedia.org/wiki/Test-and-set) and [TTAS](https://en.wikipedia.org/wiki/Test_and_test-and-set)
- [Semaphore](https://en.wikipedia.org/wiki/Semaphore_(programming)) using mutex with conditional variable and [spinning](https://en.wikipedia.org/wiki/Busy_waiting) (atomics)
